#include "stdafx.h"
#include "InventorySystem.h"
#include <iostream>
#include <string>
using namespace std;

int min(int a,int b){
	return a<b?a:b;
}

int max(int a,int b){
	return a>b?a:b;
}

int abs(int a){
	return a>0?a:(-1)*a;
}

bool PotionRH::_beenDiscovered=false;
bool PotionBA::_beenDiscovered=false;
bool PotionBD::_beenDiscovered=false;

bool PotionWA::_beenDiscovered=false;
bool PotionWD::_beenDiscovered=false;
//RH
//*************************************************************************
PotionRH::PotionRH(Character* player,DungeonMap* map){
	setInfo(RH,"Restore health (RH): restore 10 HP.",true,player,map);
	int hp = player->getHP();
	int hpMax = player->getHPMax();
	_hpStored = min(hpMax-hp,10); // restore at most 10 hp
}

void PotionRH::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover new potion RH! " + intToString(_hpStored) + " HP stored.";
		_map->setAction(action);
		discover();
	}else{
		action = "Use RH."+ intToString(_hpStored)+" HP stored.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	_map->printMap();
}

void PotionRH::useMe(){
	_player->setHP(_player->getHP()+_hpStored);
}

//BA
//*************************************************************************
PotionBA::PotionBA(Character* player,DungeonMap* map){
	setInfo(BA,"Boost Atk (BA): increase ATK by 5.",false,player,map);
	_orignalAtk = player->getAtk();
}

void PotionBA::useMe(){
	_player->setAtk(_orignalAtk+5);
}

void PotionBA::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover new potion BA!." ;
		action += " Attack increases by 5.";
		_map->setAction(action);
		discover();
	}else{
		action = "Use BA." ;
		action+=" Attack increases by 5.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	_map->printMap();
}

void PotionBA::lostEff(){
	_player->setAtk(_orignalAtk);
	synchronizeStatus(_player,_map);
	_map->statusRefresh();
}


//BD
//*************************************************************************
PotionBD::PotionBD(Character* player,DungeonMap* map){
	setInfo(BD,"Boost Def (BD): increase Def by 5.",false,player,map);
	_orignalDef = player->getDef();
}

void PotionBD::useMe(){
	_player->setDef(_orignalDef+5);
}

void PotionBD::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover new potion BD!." ;
		action += " Def increases by 5.";
		_map->setAction(action);
		discover();
	}else{
		action = "Use BD." ;
		action+=" Def increases by 5.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	_map->printMap();
}

void PotionBD::lostEff(){
	_player->setDef(_orignalDef);
	_map->setDef(_orignalDef);
	_map->statusRefresh();
}

//WA
//*************************************************************************
PotionWA::PotionWA(Character* player,DungeonMap* map){
	setInfo(WA,"Wound Atk (WA): decrease Atk by 5",false,player,map);
	_orignalAtk = player->getAtk();
	int newAtk = max(_orignalAtk-5,0);
	_atkWD = _orignalAtk - newAtk;
	if(_player->getRace()=="elves"){
		_atkWD = -5;
	}
}

void PotionWA::useMe(){
	_player->setAtk(_orignalAtk-_atkWD);
}

void PotionWA::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover new potion WA!." ;
		if(_player->getRace()=="elves"){
		action += "Change WA to BA! Attack increases by ";
		}else{
			action += " Attack decreases by ";
		}
		action += intToString(abs(_atkWD))+".";
		_map->setAction(action);
		discover();
	}else{
		action = "Use WA." ;
		if(_player->getRace()=="elves"){
		action += "Change WA to BA! Attack increases by ";
		}else{
			action += " Attack decreases by ";
		}
		action += intToString(abs(_atkWD))+".";
		_map->setAction(action);
	}
	_map->statusRefresh();
	_map->printMap();
}

void PotionWA::lostEff(){
	_player->setAtk(_orignalAtk);
	synchronizeStatus(_player,_map);
	_map->statusRefresh();
}


//WD
//*************************************************************************
PotionWD::PotionWD(Character* player,DungeonMap* map){
	setInfo(WD,"Wound Def (WD): decrease Def by 5",false,player,map);
	_orignalDef = player->getDef();
	int newDef = max(_orignalDef-5,0);
	_defWD = _orignalDef - newDef;
	if(_player->getRace()=="elves"){
		_defWD = -5;
	}
}

void PotionWD::useMe(){
	_player->setDef(_orignalDef-_defWD);
}

void PotionWD::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover new potion WD!." ;
		if(_player->getRace()=="elves"){
		action += "Change WD to BD! Def increases by ";
		}else{
			action += " Def decreases by ";
		}
		action += intToString(abs(_defWD))+".";
		_map->setAction(action);
		discover();
	}else{
		action = "Use WD." ;
		if(_player->getRace()=="elves"){
		action += "Change WD to BD! Def increases by ";
		}else{
			action += " Def decreases by ";
		}
		action += intToString(abs(_defWD))+".";
		_map->setAction(action);
	}
	_map->statusRefresh();
	_map->printMap();
}

void PotionWD::lostEff(){
	_player->setDef(_orignalDef);
	synchronizeStatus(_player,_map);
	_map->statusRefresh();
}
