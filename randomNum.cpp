#include "stdafx.h"
#include "randomNum.h"
#include <iostream>
using namespace std;

void SetSeed(){
	srand(time(0));
}

int randNumBtw(int low,int high){
	return (rand() % (high - low + 1)) + low;
}

char genEnemy(){
	int randint;
	randint=randNumBtw(1,18);
	if(1<=randint&&randint<=4) return 'w';
	if(5<=randint&&randint<=7) return 'v';
	if(8<=randint&&randint<=12) return 'n';
	if(13<=randint&&randint<=14) return 't';
	if(15<=randint&&randint<=16) return 'x';
	if(17<=randint&&randint<=18) return 'm';
	return ' ';
}


bool inBlock(posn* item,int minX,int maxX,int minY,int maxY){
	return (item->x >= minX) && (item->x <= maxX) && (item->y >= minY) && (item->y <= maxY);
}
bool inChamber1(posn* item){
	return inBlock(item,3,6,3,28);
}
bool inChamber2(posn* item){
	return inBlock(item,3,6,39,61)||inBlock(item,5,12,61,69)||inBlock(item,6,12,70,72)||inBlock(item,7,12,73,75);
}
bool inChamber3(posn* item){
	return inBlock(item,10,12,38,49);
}
bool inChamber4(posn* item){
	return inBlock(item,15,21,4,24);
}
bool inChamber5(posn* item){
	return inBlock(item,16,18,65,75)||inBlock(item,19,21,37,75);
}

posn* SpawninChamber1(){
	posn* newposn = new posn;
	newposn->x = randNumBtw(3,6);
	newposn->y = randNumBtw(3,28);
	newposn->c = ' ';
	return newposn;
}

posn* SpawninChamber2(){
	posn* newposn = new posn;
	int num = randNumBtw(1,201);
	if(1 <= num && num <= 92 ){
		newposn->x = randNumBtw(3,6);
		newposn->y = randNumBtw(39,61);
	}
	else if (92 < num && num <= 98){
		newposn->x = randNumBtw(7,12);
		newposn->y = 61;
	}
	else if (98 < num && num <=162){
		newposn->x = randNumBtw(5,12);
		newposn->y = randNumBtw(62,69);
	}
	else if(162 < num && num <=183){
		newposn->x = randNumBtw(6,12);
		newposn->y = randNumBtw(70,72);
	}
	else{
		newposn->x = randNumBtw(7,12);
		newposn->y = randNumBtw(73,75);
	}

		newposn->c = ' ';
		return newposn;
}
posn* SpawninChamber3(){
	posn* newposn = new posn;
	newposn->x = randNumBtw(10,12);
	newposn->y = randNumBtw(38,49);
	newposn->c = ' ';
	return newposn;
}

posn* SpawninChamber4(){
	posn* newposn = new posn;
	newposn->x = randNumBtw(15,21);
	newposn->y = randNumBtw(4,24);
	newposn->c = ' ';
	return newposn;
}

posn* SpawninChamber5(){
	posn* newposn = new posn;
	int num = randNumBtw(1,150);
	if(1 <= num && num <= 33){
		newposn->x = randNumBtw(16,18);
		newposn->y = randNumBtw(65,75);
	}
	else {
		newposn->x = randNumBtw(19,21);
		newposn->y = randNumBtw(37,75);
	}
	newposn->c = ' ';
	return newposn;
}

bool PosnEqual(posn* posn1,posn* posn2){
	return posn1->x == posn2->x && posn1->y == posn2->y;
}

bool SameBefore(posn** BeforeArray,posn* NowPosn,int n){
	for(int i=0 ; i < n; i++){
	if (PosnEqual(BeforeArray[i],NowPosn)){
	return true;//the before element in array has the same posn;
	}
	}
	return false;
}

posn** SetItem(){
	posn* *PosnArray = new posn*[22];
	int StairChamberNum;
	StairChamberNum = randNumBtw(1,5);
	posn *StairPosn = new posn;
	switch (StairChamberNum) {
		case 1 : StairPosn = SpawninChamber1();
		         break;
		case 2 : StairPosn = SpawninChamber2();
		         break;
		case 3 : StairPosn = SpawninChamber3();
		         break;
		case 4 : StairPosn = SpawninChamber4();
		         break;
		case 5 : StairPosn = SpawninChamber5();
		         break;
		default: break;
	}
	StairPosn->c = '\\';
	PosnArray[0] = StairPosn;    
	posn *PlayerPosn = new posn;
    int PlayerChamberNum;
    do { 
    PlayerChamberNum = randNumBtw(1,5);
    }while(PlayerChamberNum == StairChamberNum);
    switch (PlayerChamberNum) {
	case 1 : PlayerPosn = SpawninChamber1();
	         break;
	case 2 : PlayerPosn = SpawninChamber2();
	         break;
	case 3 : PlayerPosn = SpawninChamber3();
	         break;
	case 4 : PlayerPosn = SpawninChamber4();
	         break;
	case 5 : PlayerPosn = SpawninChamber5();
	         break;
	default: break;	
	}	
	PlayerPosn->c = '@';
	PosnArray[1] = PlayerPosn;	
	int i=2;
	while(i < 22){	
	posn *EnemyPosn = new posn;
	int EnemyChamberNum;
	EnemyChamberNum = randNumBtw(1,5);
	switch (EnemyChamberNum) {
				case 1 : EnemyPosn = SpawninChamber1();
				         break;
				case 2 : EnemyPosn = SpawninChamber2();
				         break;
				case 3 : EnemyPosn = SpawninChamber3();
				         break;
				case 4 : EnemyPosn = SpawninChamber4();
				         break;
				case 5 : EnemyPosn = SpawninChamber5();
				         break;
				default: break;
				}	
			while(SameBefore(PosnArray,EnemyPosn,i-1)){
				delete EnemyPosn;
				posn *EnemyPosn = new posn;
				EnemyChamberNum = randNumBtw(1,5);
				switch (EnemyChamberNum) {
						case 1 : EnemyPosn = SpawninChamber1();
						         break;
						case 2 : EnemyPosn = SpawninChamber2();
						         break;
						case 3 : EnemyPosn = SpawninChamber3();
						         break;
						case 4 : EnemyPosn = SpawninChamber4();
						         break;
						case 5 : EnemyPosn = SpawninChamber5();
						         break;
						default: break;	
				}
			}
			EnemyPosn->c = genEnemy();
			PosnArray[i] = EnemyPosn;
			i++;
		}
	return PosnArray;
}
		
