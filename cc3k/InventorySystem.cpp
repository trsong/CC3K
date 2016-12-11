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
bool PotionPH::_beenDiscovered=false;
bool PotionWA::_beenDiscovered=false;
bool PotionWD::_beenDiscovered=false;

bool GoldN::_beenDiscovered=false;
bool GoldS::_beenDiscovered=false;
bool GoldM::_beenDiscovered=false;
bool GoldD::_beenDiscovered=false;
//RH
//*************************************************************************
PotionRH::PotionRH(Character* player,DungeonMap* map){
	setInfo(RH,"Restore health (RH): restore 10 HP.",true,player,map);
	if(player!=0){
		setPlayer(player);
	}
}
void PotionRH::setPlayer(Character* player){
	int hp = player->getHP();
	int hpMax = player->getHPMax();
	_hpStored = min(hpMax-hp,10); // restore at most 10 hp	
	_player = player;
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
	 
}

void PotionRH::useMe(){
	_player->setHP(_player->getHP()+_hpStored);
}

//BA
//*************************************************************************
PotionBA::PotionBA(Character* player,DungeonMap* map){
	setInfo(BA,"Boost Atk (BA): increase ATK by 5.",false,player,map);
	if(player!=0){
		setPlayer(player);
	}
}

void PotionBA::setPlayer(Character* player){
	_orignalAtk = player->getAtk();
	_player = player;
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
	if(player!=0){
		setPlayer(player);
	}
}

void PotionBD::setPlayer(Character* player){
	_orignalDef = player->getDef();
	_player = player;
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
	 
}

void PotionBD::lostEff(){
	_player->setDef(_orignalDef);
	_map->setDef(_orignalDef);
	_map->statusRefresh();
}

//PH
//*************************************************************************
PotionPH::PotionPH(Character* player,DungeonMap* map){
	setInfo(PH,"Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)",true,player,map);
	if(player!=0){
		setPlayer(player);
	}
}

void PotionPH::setPlayer(Character* player){
	int newHP = max(player->getHP()-10,0);
	_hpWD = player->getHP()-newHP;
	if(player->getRace()=="elves"){
		_hpWD = (-1)*min(player->getHPMax()-player->getHP(),10);
	}
	_player = player;
}

void PotionPH::useMe(){
	_player->setHP(_player->getHP()-_hpWD);
}

void PotionPH::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover new potion PH!." ;
		if(_player->getRace()=="elves"){
		action += "Change PH to RH! HP restored by ";
		}else{
			action += "HP decresed by ";
		}
		action += intToString(abs(_hpWD))+".";
		_map->setAction(action);
		discover();
	}else{
		action = "Use PH." ;
		if(_player->getRace()=="elves"){
		action += "Change PH to RH! HP restored by ";
		}else{
			action += " HP decreased by ";
		}
		action += intToString(abs(_hpWD))+".";
		_map->setAction(action);
	}
	_map->statusRefresh();
	 
}



//WA
//*************************************************************************
PotionWA::PotionWA(Character* player,DungeonMap* map){
	setInfo(WA,"Wound Atk (WA): decrease Atk by 5",false,player,map);
	if(player!=0){
		setPlayer(player);
	}
}
void PotionWA::setPlayer(Character* player){
	_orignalAtk = player->getAtk();
	int newAtk = max(_orignalAtk-5,0);
	_atkWD = _orignalAtk - newAtk;
	if(player->getRace()=="elves"){
		_atkWD = -5;
	}
	_player = player;
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
	if(player!=0){
		setPlayer(player);
	}
}
void PotionWD::setPlayer(Character* player){
		_orignalDef = player->getDef();
	int newDef = max(_orignalDef-5,0);
	_defWD = _orignalDef - newDef;
	if(player->getRace()=="elves"){
		_defWD = -5;
	}
	_player = player;
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
	 
}

void PotionWD::lostEff(){
	_player->setDef(_orignalDef);
	synchronizeStatus(_player,_map);
	_map->statusRefresh();
}

//GoldN
//*************************************************************************
GoldN::GoldN(Character* player,DungeonMap* map){
	setInfo(Normal_Gold_Pile,"Normal_Gold_Pile: increase gold by 1.",true,player,map);
	if(player!=0){
		setPlayer(player);
	}
}

void GoldN::setPlayer(Character* player){
	_goldAdded = 1;
	if(player->getRace()=="dwarf") _goldAdded = 2;
	else if(player->getRace()=="orc") _goldAdded =1;
	_player = player;
}

void GoldN::useMe(){
	_player->setGold(_player->getGold()+_goldAdded);
}

void GoldN::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover a normal gold pile. Pick up " ;
		action += intToString(_goldAdded)+" gold.";
		_map->setAction(action);
		discover();
	}else{
		action = "Pick up " ;
		action+=intToString(_goldAdded)+" gold from a normal gold pile.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	 
}

//GoldS
//*************************************************************************
GoldS::GoldS(Character* player,DungeonMap* map){
	setInfo(Small_Horde,"Small_Horde: increase gold by 2.",true,player,map);
	if(player!=0){
		setPlayer(player);
	}
}

void GoldS::setPlayer(Character* player){
	_goldAdded = 2;
	if(player->getRace()=="dwarf") _goldAdded = 4;
	else if(player->getRace()=="orc") _goldAdded =1;
	_player = player;
}

void GoldS::useMe(){
	_player->setGold(_player->getGold()+_goldAdded);
}

void GoldS::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover a Small Horde. Pick up " ;
		action += intToString(_goldAdded)+" gold.";
		_map->setAction(action);
		discover();
	}else{
		action = "Pick up " ;
		action+=intToString(_goldAdded)+" gold from a Small Horde.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	 
}


//GoldM
//*************************************************************************
GoldM::GoldM(Character* player,DungeonMap* map){
	setInfo(Merchant_Horde,"Merchant_Horde: increase gold by 4.",true,player,map);
	if(player!=0){
		setPlayer(player);
	}
}

void GoldM::setPlayer(Character* player){
	_goldAdded = 4;
	if(player->getRace()=="dwarf") _goldAdded = 8;
	else if(player->getRace()=="orc") _goldAdded =2;
	_player = player;
}

void GoldM::useMe(){
	_player->setGold(_player->getGold()+_goldAdded);
}

void GoldM::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover a Merchant Horde. Pick up " ;
		action += intToString(_goldAdded)+" gold.";
		_map->setAction(action);
		discover();
	}else{
		action = "Pick up " ;
		action+=intToString(_goldAdded)+" gold from a Merchant Horde.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	 
}


//GoldD
//*************************************************************************
GoldD::GoldD(Character* player,DungeonMap* map){
	setInfo(Dragon_Horde,"Dragon_Horde: increase gold by 6.",true,player,map);
	if(player!=0){
		setPlayer(player);
	}
}

void GoldD::setPlayer(Character* player){
	_goldAdded = 6;
	if(player->getRace()=="dwarf") _goldAdded = 12;
	else if(player->getRace()=="orc") _goldAdded =3;
	_player = player;
}

void GoldD::useMe(){
	_player->setGold(_player->getGold()+_goldAdded);
}

void GoldD::notifyDisplayMap(){
	synchronizeStatus(_player,_map);
	string action;
	if(!getBeenDiscovered()){
		action  = "Discover a Dragon Horde. Pick up " ;
		action += intToString(_goldAdded)+" gold.";
		_map->setAction(action);
		discover();
	}else{
		action = "Pick up " ;
		action+=intToString(_goldAdded)+" gold from a Dragon Horde.";
		_map->setAction(action);
	}
	_map->statusRefresh();
	 
}
