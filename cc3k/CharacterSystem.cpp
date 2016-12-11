#include "stdafx.h"

#include "CharacterSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

string PC_FILE_PATH("./PCData/"),ENEMY_FILE_PATH("./EnemyData/");
//Helper functions
// charToString: Type convertion: char -> string
  string charToString(char c)
{
   stringstream ss;//create a stringstream
   ss << c;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

//synchronize mapDisplay
void synchronizeStatus(Character*player,DungeonMap*map){
	map->setStatus(player->getRace(),"",player->getHP(),player->getAtk(),player->getDef(),player->getGold(),-1);
	map->statusRefresh();
}

string getFileName(char c,string type){
	fstream GameFile;
	if (type=="PC") GameFile.open((PC_FILE_PATH+"content.txt").c_str());
	else if (type=="Enemy") GameFile.open((ENEMY_FILE_PATH+"content.txt").c_str());
	string inputStr,targetStr;
	targetStr = charToString(c);
	while(GameFile>>inputStr){
		if(inputStr==targetStr){
			GameFile>>inputStr;
			GameFile.close();
			return inputStr;
		}
	}
	GameFile.close();
	return "";
}

Character::Character(char c,string type):_type(type){
	fstream dataFile;
	string fileName;
	if (type=="PC"){
		fileName = getFileName(c,"PC");
		dataFile.open((PC_FILE_PATH+fileName).c_str());
		if(!dataFile.is_open()) cerr<<"Warning! Fail to open the game data file!"<<endl;
	}
	else if (type=="Enemy"){
		fileName = getFileName(c,"Enemy");
		dataFile.open((ENEMY_FILE_PATH+fileName).c_str());
		if(!dataFile.is_open()) cerr<<"Warning! Fail to open the game data file!"<<endl;
	}
		string tmp;
	dataFile>>tmp>>_race;
	dataFile>>tmp>>_hp;
	_hpMax=_hp;
	dataFile>>tmp>>_atk;
	dataFile>>tmp>>_def;
	dataFile>>tmp>>_gold;
	dataFile>>tmp>>_accuracy;
	dataFile.close();

}

