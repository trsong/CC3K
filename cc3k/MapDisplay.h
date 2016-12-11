#ifndef __MAPDISPLAY_H__
#define __MAPDISPLAY_H__
#include <iostream>
const int MAPWIDTH=80;
const int MAPHEIGHT=25;
const int STATUSHEIGHT=5;
class DungeonMap
{
public:
	DungeonMap();
	~DungeonMap();
	void changeMap(int x,int y,char c){Map[x][y]=c;};
	void printMap();
	void statusRefresh();
	void setRace(std::string race){_race=race;}
	void setAction(std::string action){_action=action;}
	void setHp(int hp){_hp=hp;}
	void setAtk(int atk){_atk=atk;}
	void setDef(int def){_def=def;}
	void setGold(int gold){_gold=gold;}
	void setFloor(int floorNum){_floorNum=floorNum;}
	void setStatus(std::string race="",std::string action="",int hp=-1,int atk=-1,int def=-1,int gold=-1,int floorNum=-1);

	char getMap(int x,int y){return Map[x][y];}
	std::string getAction(){return _action;}
private:
	int _x,_y;
	int _floorNum;
	std::string _race;
	std::string _action;
	int _hp;
	int _gold;
	int _atk;
	int _def;
	char **Map;
	char **Status;
};

std::string intToString(int number);
#endif

/* Test
#include <iostream>
#include "MapDisplay.h"
using namespace std;

int main()
{
	DungeonMap* map=new DungeonMap;
	map->setStatus("Human","Stay clam!",100,-1,-1,10,-1);
	map->changeMap(3,3,'@');
	map->statusRefresh();
	map->printMap();
	int i;
	cin>>i;
	return 0;
}

*/