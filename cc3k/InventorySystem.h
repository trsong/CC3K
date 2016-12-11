#ifndef _INVENTORYSYSYEM_H_
#define _INVENTORYSYSYEM_H_
#include <iostream>
#include "CharacterSystem.h"
#include "MapDisplay.h"

//extern class CharacterSystem;
enum itemName
{
	RH, //Restore health (RH): restore up to 10 HP (cannot exceed maximum prescribed by race)
	BA, //Boost Atk (BA): increase ATK by 5
	BD,	//Boost Def (BD): increase Def by 5
	PH, //Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)
	WA, //Wound Atk (WA): decrease Atk by 5
	WD, //Wound Def (WD): decrease Def by 5
	Normal_Gold_Pile, // val = 1  N   
	Small_Horde, // val = 2		  S
	Merchant_Horde, // val = 4    M
	Dragon_Horde // val = 6       
};

static const char * ItemList[] = {	"RH","BA","BD",	"PH", "WA", "WD", "Normal_Gold_Pile", "Small_Horde", "Merchant_Horde", "Dragon_Horde"};
extern class Grid;
class Item{
public:

	virtual void useMe()=0;
	virtual void lostEff()=0;
	virtual void notifyDisplayMap()=0;

	void setInfo(int ID,std::string usage,bool permanentEffect,Character* player,DungeonMap* map){
		_ID = ID; _usage = usage; _permanentEffect = permanentEffect;_player=player;_map=map;
	}
	virtual void setPlayer(Character *player)=0;
	virtual int getID(){return _ID;}
	virtual std::string getUsage(){return _usage;}
	virtual bool isPermanent(){return _permanentEffect;}
	virtual Character* getPlayer(){return _player;}
	virtual bool getBeenDiscovered()=0;
	friend class Grid;

protected:
	int _ID;
	std::string _usage;
	bool _permanentEffect;
	Character * _player;
	DungeonMap *_map;
};


class PotionRH: public Item{
public:
	PotionRH(Character* player,DungeonMap *map);
	
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;}
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _hpStored;
	static bool _beenDiscovered;
};


class PotionBA: public Item{
public:
	PotionBA(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _orignalAtk;
	static bool _beenDiscovered;
};

class PotionBD: public Item{
public:
	PotionBD(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _orignalDef;
	static bool _beenDiscovered;
};


class PotionPH: public Item{
public:
	PotionPH(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;}
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _hpWD;
	static bool _beenDiscovered;
};


class PotionWA: public Item{
public:
	PotionWA(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _orignalAtk;
	int _atkWD;
	static bool _beenDiscovered;
};

class PotionWD: public Item{
public:
	PotionWD(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _orignalDef;
	int _defWD;
	static bool _beenDiscovered;
};

class GoldN:public Item{
public:
	GoldN(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;};
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _goldAdded;
	static bool _beenDiscovered;
};

class GoldS:public Item{
public:
	GoldS(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;};
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _goldAdded;
	static bool _beenDiscovered;
};

class GoldM:public Item{
public:
	GoldM(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;};
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _goldAdded;
	static bool _beenDiscovered;
};

class GoldD:public Item{
public:
	GoldD(Character* player,DungeonMap *map);
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	virtual bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;};
	virtual void setPlayer(Character *player);
	friend class Grid;
private:
	int _goldAdded;
	static bool _beenDiscovered;
};
#endif
/* Test
#include <iostream>
#include "MapDisplay.h"
#include "InventorySystem.h"
#include "CharacterSystem.h"
using namespace std;

int main()
{
	DungeonMap* map=new DungeonMap;
	map->setStatus("Human","Stay clam!",100,-1,-1,10,-1);
	map->changeMap(3,3,'@');
	map->statusRefresh();
	map->printMap();
	cout<<endl;
	// test Potion constructor
	CharacterSystem * player = new Character('h',"PC");
	Item * myPotion = new PotionRH(player,map);
	myPotion->notifyDisplayMap();
	map->printMap();
	
	// test static member/method
	cout<<myPotion->getBeenDiscovered()<<endl;
	myPotion->discover();
	cout<<myPotion->getBeenDiscovered()<<endl;
	int i;
	cin>>i;
	return 0;
}
*/

/* Test 2
#include <iostream>
#include "MapDisplay.h"
#include "InventorySystem.h"
#include "CharacterSystem.h"
using namespace std;

int main()
{
	DungeonMap* map=new DungeonMap;
	Character * player = new Character('o',"PC");
	player->setAtk(3);
	player->setHP(5);
	synchronizeStatus(player,map);
	Potion * myPotion ;
	
	map->printMap();
	
	cout<<"============================================"<<endl;
	//test PotionPH
	myPotion = new PotionPH(player,map);
	myPotion->useMe();
	myPotion->notifyDisplayMap();
	//myPotion->lostEff();

	cout<<"============================================"<<endl;
	map->printMap();
	
	myPotion = new PotionBD(player,map);
	myPotion->useMe();
	myPotion->notifyDisplayMap();
	myPotion->lostEff();
	
	int i;
	cin>>i;
	return 0;
}
*/