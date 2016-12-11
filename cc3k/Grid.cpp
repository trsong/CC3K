#include "stdafx.h"
#include "Grid.h"
#include <string>
#include <vector>
using namespace std;

bool Grid::_merchantBeenAttacked = false;
// V(ampire), W(erewolf), N(goblin), M(erchant), D(ragon),X(Phoenix), T(roll), M(erchant).
// o normal gold pile 'N'
// S dragon horde 'G'
// s small horde 'S'

// 5|0|4
// -----
// 3| |2
// -----
// 7|1|6

//helper functions

void directionShift(int& x,int&y,int direction){
	switch (direction)
	{
	case nw:x--;y--;break;
	case no:x--;	break;
	case ne:x--;y++;break;
	case we:y--;	break;
	case ea:y++;	break;
	case sw:x++;y--;break;
	case so:x++;	break;
	case se:x++;y++;break;
	default:
		break;
	}
}

bool moveable(Grid* grid,Cell* targetCell,int direction){
	int x,y;
	x = targetCell->getX();
	y = targetCell->getY();
	directionShift(x,y,direction);
	posn* tmp = new posn;
	tmp->c=' ';tmp->x=x;tmp->y=y;
	bool result;
	if(targetCell->getType()=="PC") {
		result = inWall(tmp)&&(grid->_grid[x][y]==0);
	}
	else result = inChamber(tmp)&&(grid->_grid[x][y]==0);
	delete tmp;
	return result;
}
//
Grid::Grid(int floorNum):_currentGrid('.'),_floorNum(floorNum)
{
	_map = new DungeonMap;

	_map->setFloor(_floorNum);
	_map->statusRefresh();
	_grid = new Cell**[MAPHEIGHT];
	for(int row=0;row<MAPHEIGHT;row++){
		_grid[row] = new Cell*[MAPWIDTH];
	}
	gridInit();

	int randomGeneratorSize = 42;
	posn ** randomGenerator = SetItem();
	posn ** dragonGenerator = SetDragon(randomGenerator);
	int dragonGeneratorSize = (dragonGenerator==0)?0:dragonGenerator[0]->x;
	posn *tmp = 0;
	for(int i=0;i<randomGeneratorSize;i++){
		tmp = randomGenerator[i];
		int x = tmp->x;
		int y = tmp->y;
		char c = tmp->c;
		Cell* goldCell;
		switch (c)
		{
		case '@':{
			_player = new Cell(x,y,"PC",'h',_map);
			_map->changeMap(x,y,'@');
			_grid[x][y] = _player;
			break;
				 }
		case '\\':{
			_staircase = new Cell(tmp->x,tmp->y,"\\",'\\',_map);
			_map->changeMap(x,y,'\\');
			_grid[x][y]=_staircase;
			break;}
		// non-Dragon Enemy
		case 'v':case 'w':case 'n':case 'm':case 'x':case 't':{
			Cell* enemyCell = new Cell(tmp->x,tmp->y,"Enemy",tmp->c,_map);
			//
			_enemyStack.push_back(enemyCell);
			_map->changeMap(x,y,c-('a'-'A'));
			_grid[x][y] = enemyCell;
			break;}
		// item: potion
		case 'H':case 'A':case 'D':case 'h':case 'a':case 'd':{
			Cell* potionCell = new Cell(x,y,"Item",c,_map);
			_itemStack.push_back(potionCell);
			_map->changeMap(x,y,'P');
			_grid[x][y] = potionCell;
			break;}
		// small horde 'S'
		case 's':{
			goldCell = new Cell(x,y,"Item",'S',_map);
			_itemStack.push_back(goldCell);
			_map->changeMap(x,y,'G');
			_grid[x][y]=goldCell;
			break;}
		// normal 'N'
		case 'o':{
			 goldCell = new Cell(x,y,"Item",'N',_map);
			_itemStack.push_back(goldCell);
			_map->changeMap(x,y,'G');
			_grid[x][y]=goldCell;
			break;}
		// Dragon horde 'G'
		case 'S':{
			goldCell = new Cell(x,y,"Item",'G',_map);
			_itemStack.push_back(goldCell);
			_dragonHordeStack.push_back(goldCell);
			_map->changeMap(x,y,'G');
			_grid[x][y]=goldCell;
			break;
				 }
		default:
			break;

		}	
	}
	delete[] randomGenerator;
	// generate Dragon
	for(int i=1;i<dragonGeneratorSize+1;i++){
		tmp = dragonGenerator[i];
		int x = tmp->x;
		int y = tmp->y;
		Cell * dragonCell = new Cell(x,y,"Enemy",'d',_map);
		dragonCell->setHostile(false);
		dragonCell->setGragonHordeCell(_dragonHordeStack[i-1]);
		_enemyStack.push_back(dragonCell);
		_map->changeMap(x,y,'D');
		_grid[x][y]=dragonCell;
	}
	delete[] dragonGenerator;

	synchronizeStatus(_player->getCharacter(),_map);
}
void Grid::ChangeRace(char c){
	//delete _player->getCharacter();
	Character *tmp = new Character(c,"PC");
	_player->setCharacter(tmp);
	synchronizeStatus(tmp,_map);
	_map->statusRefresh();
}

void Grid::enemyMove(){
	int maxStep = 40;
	int step=0;
	for(int i=0;i<_enemyMoveStack.size();i++){
		Cell * enemyCell = _enemyMoveStack[i];
		step=0;
		while (true)
		{
			if(enemyCell->getIdentity()=='d') break;
			enemyCell->setMovingDirection(randNumBtw(0,8));
			if(moveable(this,enemyCell,enemyCell->getMovingDirection())) {
				int x=enemyCell->getX(),y=enemyCell->getY();
				int oldX =x, oldY=y;
				directionShift(x,y,enemyCell->getMovingDirection());
				enemyCell->setX(x);
				enemyCell->setY(y);
				_grid[x][y] = enemyCell;
				_grid[oldX][oldY]=0;
				_map->changeMap(x,y,enemyCell->getIdentity()-('a'-'A'));
				_map->changeMap(oldX,oldY,'.');
				break;
			}else if(step>maxStep){
				break;
			}
			step++;
		}
	}
	_enemyMoveStack.clear();
}

void Grid::enemyAttack(){
	int xPC = _player->getX();
	int yPC = _player->getY();
	int miss=0;
	string action=_map->getAction();
	int hpOld = _player->_character->getHP();
	for(int i=0;i<_enemyStack.size();i++){
		Cell* enemyCell = _enemyStack[i];
		int xEnemy = enemyCell->getX();
		int yEnemy = enemyCell->getY();
		if((abs(xPC-xEnemy)<=1)&&(abs(yPC-yEnemy)<=1)&&(enemyCell->getHostile()==true)){
			if(enemyCell->getIdentity()!='m'){
				if(randNumBtw(0,1)==0){
					enemyCell->action(_player);
					action+= enemyCell->getCharacter()->getRace()+" ";
				}else{
					miss++;
				}
			}else if(_merchantBeenAttacked==true)
			{
				if(randNumBtw(0,1)==0){
					enemyCell->action(_player);
					action+= enemyCell->getCharacter()->getRace()+" ";
				}else{
					miss++;
				}
			}
		}else if(enemyCell->getIdentity()!='d'){
				_enemyMoveStack.push_back(enemyCell);
		}
		
	}

	int hpWD = hpOld - _player->getCharacter()->getHP();
	if (hpWD!=0)
	{
		action+= "deal "+intToString(hpWD);
		action+=" damage to PC." ;
		if(miss!=0){
			action+="Enemy:";
			action+=intToString(miss)+" attack miss.";
		}
		_map->setAction(action);
		_map->statusRefresh();
	}else if(miss!=0){
		action+="Enemy:";
		action+=intToString(miss)+" attack miss.";
		_map->setAction(action);
		_map->statusRefresh();
	}
	_map->setAction("");
	
}

string Grid::getItemInfo(int x,int y){
	string output="";
	Cell * tmp = _grid[x][y];
	if(tmp==0) return output;
	if (tmp->getType()=="Item"){
		if(tmp->getItem()->getBeenDiscovered()==false){
			output += "Find new item.";
			return output;
		}else
		{
			output+="Find ";
			output +=ItemList[tmp->getItem()->getID()];
			output+=".";
			return output;
		}
	}else if(tmp->getType()=="\\"){
		output+="Staircase!";
		return output;
	}
	return "";
}
string Grid::searchItem(int x,int y){
	string output="";
	output+=getItemInfo(x-1,y-1);
	output+=getItemInfo(x-1,y);
	output+=getItemInfo(x-1,y+1);

	output+=getItemInfo(x,y-1);
	output+=getItemInfo(x,y+1);

	output+=getItemInfo(x+1,y-1);
	output+=getItemInfo(x+1,y);
	output+=getItemInfo(x+1,y-1);
	return output;
}

Grid::~Grid()
{
	for(int row=0;row<MAPHEIGHT;row++){
		delete[] _grid;
	}
	delete _map;
	for(int i=0;i<_enemyStack.size();i++){
		delete _enemyStack[i];
	}
	for(int i=0;i<_itemStack.size();i++){
		delete _itemStack[i];
	}
	delete _player;
	delete _staircase;
}

void Grid::gridInit(){
	for(int row=0;row<MAPHEIGHT;row++){
		for(int col=0;col<MAPWIDTH;col++){
			_grid[row][col]=0;
		}
	}
}

int Grid::playerMove(int direction){
	int x,oldX,y,oldY;
	x=oldX= _player->getX();
	y=oldY = _player->getY();
	directionShift(x,y,direction);
	Cell *targetCell = _grid[x][y];
	posn tmp = {' ',x,y};

	if(!inWall(&tmp)) return 0;
	if(targetCell==0){
		
	}
	else if((targetCell->getType()=="\\")&&(direction==we)) return 2;
	else if(targetCell->getBeenProtected()) return 0;
	else if(targetCell->getType()=="Item"){
		targetCell->setItemUser(_player->getCharacter());
		targetCell->getItem()->useMe();
		targetCell->getItem()->notifyDisplayMap();
		delete targetCell;
	}
	_grid[x][y]=_player;
	_grid[oldX][oldY]=0;
	_player->setX(x);_player->setY(y);
	_map->changeMap(oldX,oldY,_currentGrid);
	_currentGrid = _map->getMap(x,y);
	_currentGrid = (_currentGrid=='G')?'.':_currentGrid;
	_map->changeMap(x,y,'@');
	string action="";
	action +="PC move ";
	action +=  allMovingDirectionList[direction];
	action +=".";
	if(targetCell==0){
		_map->setAction(action+searchItem(x,y));
	}
	_map->statusRefresh();
	
	return 1;
}


bool Grid::playerUsePotion(int direction){
	int x =_player->getX();
	int y =_player->getY();
	directionShift(x,y,direction);
	Cell * potionCell = _grid[x][y];
	if(potionCell==0) return false;
	if(potionCell->getIdentity()=='H'||
		potionCell->getIdentity()=='A'||
		potionCell->getIdentity()=='D'||
		potionCell->getIdentity()=='h'||
		potionCell->getIdentity()=='a'||
		potionCell->getIdentity()=='d'){
			_player->action(potionCell);
			return true;
	}
	return false;
}

bool Grid::playerAttack(int direction){
	int x =_player->getX();
	int y =_player->getY();
	synchronizeStatus(_player->getCharacter(),_map);
	directionShift(x,y,direction);
	Cell * enemyCell = _grid[x][y];
	if(enemyCell==0) return false;
	if(enemyCell->getIdentity()=='v'||
	  enemyCell->getIdentity()=='w'||
	  enemyCell->getIdentity()=='n'||
	  enemyCell->getIdentity()=='m'||
	  enemyCell->getIdentity()=='x'||
	  enemyCell->getIdentity()=='t'||
	  enemyCell->getIdentity()=='d'){
		_player->action(enemyCell);
		if(enemyCell->getIdentity()=='d') enemyCell->setHostile(true);
		if(enemyCell->getIdentity()=='d'&&enemyCell->getDead()==true) enemyCell->getGragonHordeCell()->setBeenProtected(false);
		if(enemyCell->getIdentity()=='m') setMerchantBeenAttacked(true);
	//	if((enemyCell->getIdentity()=='m')&&(enemyCell->getDead()==true)){

	//	}
		return true;
	}
	return false;
}


void Grid::changeState(){
	for(int i=0;i<_enemyStack.size();i++){
		int x,y;
		Cell * enemyCell = _enemyStack[i];
		if(x=enemyCell->getX(),y=enemyCell->getY(),(enemyCell->getDead()==true)){
			if(enemyCell->getIdentity()=='m'){
				_map->changeMap(x,y,'.');
				_grid[x][y]=0;
				_enemyStack.erase(_enemyStack.begin()+i);
				int x,y;
				x=enemyCell->getX();
				y=enemyCell->getY();
				Cell* merchantCell = new Cell(x,y,"Item",'M',_map);
				merchantCell->setType("Item");
				_grid[x][y]=merchantCell;
				merchantCell->setDead(false);
				_itemStack.push_back(merchantCell);
				_map->changeMap(x,y,'G');
				string action = _map->getAction();
				action+=" Find a merchant horde!";
				_map->setAction(action);
				_map->statusRefresh();
				
			}else{
				_map->changeMap(x,y,'.');
				_grid[x][y]=0;
				_enemyStack.erase(_enemyStack.begin()+i);
			}
		}
	}
	for(int i=0;i<_itemStack.size();i++){
		int x,y;
		Cell * itemCell = _itemStack[i];
		if(x=itemCell->getX(),y=itemCell->getY(),itemCell->getDead()==true){
			_grid[x][y]=0;
			_map->changeMap(x,y,'.');
			_itemStack.erase(_itemStack.begin()+i);
		}
	}
	enemyAttack();
	enemyMove();

}

void Grid::setPlayer(Cell*player){
	_map->changeMap(_player->getX(),_player->getY(),'.');
	player->setX(_player->getX());
	player->setY(_player->getY());

	char id = player->getIdentity();
	Character* tmp = new Character(id,"PC");
	player->getCharacter()->setAtk(tmp->getAtk());
	player->getCharacter()->setDef(tmp->getDef());
	cout<<"ID::"<<player->getCharacter()->getRace()<<endl;
	_player=player;
	_map->changeMap(_player->getX(),_player->getY(),'@');
	synchronizeStatus(_player->getCharacter(),_map);
}
