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
	Normal_Gold_Pile, 
	Small_Horde,
	Merchant_Horde,
	Dragon_Horde
};


class Potion{
public:
	virtual void useMe()=0;
	virtual void lostEff()=0;
	virtual void notifyDisplayMap()=0;

	void setInfo(int ID,std::string usage,bool permanentEffect,Character* player,DungeonMap* map){
		_ID = ID; _usage = usage; _permanentEffect = permanentEffect;_player=player;_map=map;
	}

	virtual int getID(){return _ID;}
	virtual std::string getUsage(){return _usage;}
	virtual bool isPermanent(){return _permanentEffect;}
	virtual Character* getPlayer(){return _player;}

protected:
	int _ID;
	std::string _usage;
	bool _permanentEffect;
	Character * _player;
	DungeonMap *_map;
};


class PotionRH: public Potion{
public:
	PotionRH(Character* player,DungeonMap *map);
	~PotionRH(){delete this;}
	
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	static bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff(){return;}
private:
	int _hpStored;
	static bool _beenDiscovered;
};


class PotionBA: public Potion{
public:
	PotionBA(Character* player,DungeonMap *map);
	~PotionBA(){delete this;}
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	static bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
private:
	int _orignalAtk;
	static bool _beenDiscovered;
};

class PotionBD: public Potion{
public:
	PotionBD(Character* player,DungeonMap *map);
	~PotionBD(){delete this;}
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	static bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
private:
	int _orignalDef;
	static bool _beenDiscovered;
};

class PotionWA: public Potion{
public:
	PotionWA(Character* player,DungeonMap *map);
	~PotionWA(){delete this;}
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	static bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
private:
	int _orignalAtk;
	int _atkWD;
	static bool _beenDiscovered;
};

class PotionWD: public Potion{
public:
	PotionWD(Character* player,DungeonMap *map);
	~PotionWD(){delete this;}
	static void discover(){_beenDiscovered=true;}
	static void initBeenDiscover(){_beenDiscovered=false;}
	static bool getBeenDiscovered(){return _beenDiscovered;}
	virtual void useMe();
	virtual void notifyDisplayMap();
	virtual void lostEff();
private:
	int _orignalDef;
	int _defWD;
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
	Potion * myPotion = new PotionRH(player,map);
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