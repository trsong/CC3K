#include "stdafx.h"
#include <iostream>
#include "MapDisplay.h"
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

string intToString(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

DungeonMap::DungeonMap():_x(-1),_y(-1),_race(""),_floorNum(1),_gold(0),_atk(0),_def(0),_hp(0)
{
	Map = new char*[MAPHEIGHT];
	Status = new char*[STATUSHEIGHT];
	for(int row=0;row<MAPHEIGHT;row++){
		Map[row]=new char[MAPWIDTH+1];
	}


	fstream mapFile("./Map/Map.txt");
	for(int row=0;row<MAPHEIGHT;row++){
		string rowStr;
		getline(mapFile,rowStr);

		
		strcpy(Map[row],rowStr.c_str());
	}
	
	mapFile.close();
	

	for(int i=0;i<STATUSHEIGHT;i++){
		Status[i]=new char[MAPWIDTH+100];
	}
	statusRefresh();
}

DungeonMap::~DungeonMap()
{
	for(int i=0;i<MAPHEIGHT;i++){
		delete[] Map[i];
	}
	delete Map;
	for(int i=0;i<STATUSHEIGHT;i++){
		delete[] Status[i];
	}
	delete Status;
}


void DungeonMap::printMap(){
	for(int row=0;row<MAPHEIGHT;row++){
		cout<<Map[row]<<endl;
	}
	for(int row=0;row<STATUSHEIGHT;row++){
		cout<<Status[row]<<endl;
	}
}

void DungeonMap::statusRefresh(){
	if(!Status){
		for(int i=0;i<STATUSHEIGHT;i++){
			delete[] Status[i];
		}
	}
	string ln[5];
	ln[0] = "Race: "+_race+" Gold: "+intToString(_gold);
	int numOfSpaces=(69-(ln[0].length()));
	string space(numOfSpaces,' ');
	ln[0]+=space+"Floor "+intToString(_floorNum);
	ln[1] ="HP: "+intToString(_hp);
	ln[2] ="Atk: "+intToString(_atk);
	ln[3] ="Def: "+intToString(_def);
	ln[4] ="Action: "+_action;

	for(int row=0;row<STATUSHEIGHT;row++){
		strcpy(Status[row],ln[row].c_str());
	}

}
void DungeonMap::setStatus(string race,string action,int hp,int atk,int def,int gold,int floorNum){
	if(race!="") setRace(race);
	if(action!="") setAction(action);
	if(hp!=-1) setHp(hp);
	if(atk!=-1) setAtk(atk);
	if(def!=-1) setDef(def);
	if(gold!=-1) setGold(gold);
	if(floorNum!=-1) setFloor(floorNum);
}
