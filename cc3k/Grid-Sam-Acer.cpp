#include "stdafx.h"
#include "Grid.h"
#include <string>

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
		result = inWall(tmp)&&((grid->_grid[x][y]==0)||grid->_grid[x][y]->getBeenProtected()==false);
	}else result = inChamber(tmp)&&((grid->_grid[x][y]==0)||grid->_grid[x][y]->getBeenProtected()==false);
	delete tmp;
	return result;
}
//
Grid::Grid()
{
	_map = new DungeonMap;
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
			Cell* enemyCell = new Cell(x,y,"Enemy",c,_map);
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
		dragonCell->setGragonHordeCell(_dragonHordeStack[i-1]);
		_enemyStack.push_back(dragonCell);
		dragonCell->setHostile(false);
		_map->changeMap(x,y,'D');
		_grid[x][y]=dragonCell;
	}
	delete[] dragonGenerator;

	synchronizeStatus(_player->getCharacter(),_map);
}
void Grid::ChangeRace(char c){
	delete _player->getCharacter();
	Character *tmp = new Character(c,"PC");
	_player->setCharacter(tmp);
}

void Grid::enemyMove(){
	int maxStep = 40;
	int step=0;
	for(int i=0;i<_enemyMoveStack.size();i++){
		Cell * enemyCell = _enemyStack[i];
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
	string action("");
	for(int i=0;i<_enemyStack.size();i++){
		Cell* enemyCell = _enemyStack[i];
		int xEnemy = enemyCell->getX();
		int yEnemy = enemyCell->getY();
		if((abs(xPC-xEnemy)<=1)&&(abs(yPC-yEnemy)<=1)&&enemyCell->getHostile()){
			if(enemyCell->getIdentity()!='m'){
			enemyCell->action(_player);
			action+= enemyCell->getCharacter()->getRace()+" ";
			}else if(_merchantBeenAttacked==true)
			{
			enemyCell->action(_player);
			action+= enemyCell->getCharacter()->getRace()+" ";
			}else if(enemyCell->getIdentity()!='m'&&enemyCell->getIdentity()!='d'){
				_enemyMoveStack.push_back(enemyCell);
			}
		}
	}
	int hpWD = _player->getCharacter()->getHPMax() - _player->getCharacter()->getHP();
	if (hpWD!=0)
	{
		action+= "deal "+intToString(hpWD);
		action+=" damage to PC." ;
		_map->setAction(action);
		_map->statusRefresh();
	}
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
