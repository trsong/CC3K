#pragma warning(disable: 4996)

#include "stdafx.h"
#include <iostream>
#include "MapDisplay.h"
#include "InventorySystem.h"
#include "CharacterSystem.h"
using namespace std;

int main()
{
	DungeonMap* map=new DungeonMap;
	Character * player = new Character('e',"PC");
	player->setAtk(3);
	synchronizeStatus(player,map);
	Potion * myPotion ;
	map->printMap();
	cout<<"============================================"<<endl;
	//test PotionWD
	myPotion = new PotionWD(player,map);
	myPotion->useMe();
	myPotion->notifyDisplayMap();
	myPotion->lostEff();

	myPotion = new PotionWD(player,map);
	myPotion->useMe();
	myPotion->notifyDisplayMap();
	myPotion->lostEff();	
	cout<<"============================================"<<endl;
	map->printMap();
	/*
	myPotion = new PotionBD(player,map);
	myPotion->useMe();
	myPotion->notifyDisplayMap();
	myPotion->lostEff();
	*/
	int i;
	cin>>i;
	return 0;
}