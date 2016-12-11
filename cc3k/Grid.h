#ifndef _GRID_H_
#define _GRID_H_
#include <iostream>
#include <vector>
#include "Cell.h"
#include "MapDisplay.h"
#include "randomNum.h"
#include "InventorySystem.h"
#include "CharacterSystem.h"


extern const int MAPHEIGHT;
extern const int MAPWIDTH;
extern struct posn;

using namespace std;

class Grid
{
public:
	Grid(int floorNum);
	~Grid();
	static void setMerchantBeenAttacked(bool merchantBeenAttacked){_merchantBeenAttacked=merchantBeenAttacked;}
	void ChangeRace(char c);
	Cell* getPlayer(){return _player;}
	void setPlayer(Cell*player);
	void gridInit();
	void printMap(){_map->printMap();}
	void enemyMove();
	void enemyAttack();
	int playerMove(int direction);
	bool playerAttack(int direction);
	bool playerUsePotion(int direction);
	friend bool moveable(Grid*,Cell*,int);
	void changeState();

	bool checkPlayerDeath(){return _player->getDead();};
	int score(){
		int finalScore= _player->getCharacter()->getGold();
		if(_player->getIdentity()=='h') finalScore=(int)finalScore*1.5;
		return finalScore;
	}
	string searchItem(int x,int y);
	
private:
	int _floorNum;
	Cell ***  _grid;
	DungeonMap *_map;
	char _currentGrid;
	string getItemInfo(int x,int y);
	vector<Cell*> _itemStack;
	vector<Cell*> _enemyMoveStack;
	vector<Cell*> _enemyStack;
	vector<Cell*> _dragonHordeStack;
	vector<Cell*> _potionUsed;
	Cell * _player;
	Cell * _staircase;
	static bool _merchantBeenAttacked;
};

#endif

/*
#include <iostream>
#include "Grid.h"
using namespace std;

int main(){
	SetSeed();
	Grid* grid = new Grid;
	grid->printMap();
	grid->enemyAttack();
	grid->printMap();
	grid->enemyMove();
	grid->printMap();
	
	//delete grid;
	int i;
	cin>>i;
	return 0;

}
*/