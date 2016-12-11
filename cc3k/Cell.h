#ifndef _CELL_H_
#define _CELL_H_
#include "CharacterSystem.h"
#include "InventorySystem.h"
#include "MapDisplay.h"
#include "randomNum.h"
#include <iostream>
using namespace std;

// 5|0|4
// -----
// 3| |2
// -----
// 7|1|6
enum allMovingDirections{
	no,so,ea,we,ne,nw,se,sw
};
static const char * allMovingDirectionList[] ={"no","so","ea","we","ne","nw","se","sw"};
extern class Grid;
class Cell{
public:
	Cell(int x,int y,string type,char identity,DungeonMap* map);
	~Cell(){
		delete _character;
		delete _item;
	}
	int getX(){return _x;}
	int getY(){return _y;}
	char getIdentity(){return _identity;}
	string getType(){return _type;}
	bool getDead(){return _dead;}
	int getMovingDirection(){return _movingDirection;}
	Character *getCharacter(){return _character;}
	Item * getItem(){return _item;}
	bool getBeenProtected(){return _beenProtected;}
	Cell* getGragonHordeCell(){return _dragonHordeCell;}
	bool getHostile(){return _hostile;}

	void setX(int x){_x=x;}
	void setY(int y){_y=y;}
	void setIdentity(char identity){_identity=identity;}
	void setType(string type){_type=type;}
	void setDead(bool dead){_dead=dead;}
	void setMovingDirection(int movingDirction){_movingDirection=movingDirction;}
	void setCharacter(Character* character){_character=character;}
	void setBeenProtected(bool beenProtected){_beenProtected=beenProtected;} 
	void setGragonHordeCell(Cell* dragonHordeCell){_dragonHordeCell=dragonHordeCell;}
	void setHostile(bool hostile){_hostile=hostile;}
	void setItemUser(Character* player){_item->setPlayer(player);}

	void action(Cell*);
	friend bool moveable(Grid*,Cell*,int);
	friend class Grid;
	void testUse(Cell*inputCell);
private:
	DungeonMap * _map;
	Character * _character;
	Item* _item;
	int _x,_y;
	int _movingDirection; //no,so,ea,we,ne,nw,se,sw:
	string _type; //I E(nemy) P(otion)
	char _identity; // h o e ...
	bool _dead;
	bool _beenProtected;
	Cell * _dragonHordeCell;
	bool _hostile;
	
};
#endif

/*
#include <iostream>
#include "Cell.h"
using namespace std;

int main()
{
	DungeonMap* map=new DungeonMap;
	Cell * playerCell = new Cell(-1,-1,"PC",'h',map);
	Cell * enemyCell = new Cell(-1,-1,"Enemy",'x',map);
	synchronizeStatus(playerCell->getCharacter(),map);
	Cell * itemCell = new Cell(-1,-1,"Item",'G',map);
	map->printMap();
	// Test one: player use item
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"Test one: player use item"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	
	playerCell->action(itemCell);
	playerCell->action(itemCell);
	// Test two: player atk enemy
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"Test two: player atk enemy"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	playerCell->action(enemyCell);
	// Test three: enemy atk player
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"Test three: enemy atk player"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	enemyCell->action(playerCell);
	
	playerCell->action(enemyCell);
	int i;
	cin>>i;
	return 0;
*/