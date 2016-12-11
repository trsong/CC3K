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
	randint = randNumBtw(1,18);
	if(1 <= randint && randint <= 4) return 'w';
	if(5 <= randint && randint <= 7) return 'v';
	if(8 <= randint && randint <= 12) return 'n';
	if(13 <= randint && randint <= 14) return 't';
	if(15 <= randint && randint <= 16) return 'x';
	if(17 <= randint && randint <= 18) return 'm';
	return ' ';
}

char genPotion(){
	int randint;
	randint = randNumBtw(1,6);
	if(randint == 1) return 'H';
	if(randint == 2) return 'A';
	if(randint == 3) return 'D';
	if(randint == 4) return 'h';
	if(randint == 5) return 'a';
	if(randint == 6) return 'd';
	return ' ';
 }


// o normal gold pile
// S dragon horde
// s small horde
char genGold(){ 
	int randint;
	randint = randNumBtw(1,8);
	if(1 <= randint && randint <= 5) return 'o';
	if(randint == 6) return 'S';
	if(randint == 7 || randint == 8) return 's';
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
bool inChamber(posn* item){
	if (inChamber1(item) || inChamber2(item) || inChamber3(item) || inChamber4(item) || inChamber5(item)){
		return true;
	}
	else {
		return false;
	}
}
bool inSide(posn* item){
	if(inBlock(item,3,6,28,28) || inBlock(item,10,12,49,49) || inBlock(item,15,21,24,24) || inBlock(item,16,21,75,75)
	|| inBlock(item,3,4,61,61) || inBlock(item,5,5,70,70) || inBlock(item,6,6,73,73) || inBlock(item,7,12,75,75)){
		return true;
	}
	else{
		return false;
	}
}
bool inPassage(posn* item){
	return inBlock(item,7,14,13,13)||inBlock(item,8,20,31,31)||inBlock(item,4,8,33,33)||inBlock(item,7,9,43,43)||inBlock(item,13,18,43,43)
		||inBlock(item,11,16,54,54)||inBlock(item,13,15,69,69)||inBlock(item,4,4,29,38)||inBlock(item,8,8,31,43)||inBlock(item,11,11,13,31)
		||inBlock(item,11,11,54,60)||inBlock(item,16,16,31,54)||inBlock(item,20,20,25,36);
}
bool inWall(posn* item){
	return inPassage(item)||inChamber(item);
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
		return true;
		}
	}
	return false;
}

posn** SetItem(){
	posn* *PosnArray = new posn*[42];
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
	while(inSide(StairPosn)){
		delete StairPosn;
		StairChamberNum = randNumBtw(1,5);
		StairPosn = new posn;
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
				EnemyPosn = new posn;
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
	int t = 22;
	while(t < 32){
		posn *PotionPosn = new posn;
		int PotionChamberNum;
		PotionChamberNum = randNumBtw(1,5);
		switch (PotionChamberNum) {
					case 1 : PotionPosn = SpawninChamber1();
							 break;
					case 2 : PotionPosn = SpawninChamber2();
							 break;
					case 3 : PotionPosn = SpawninChamber3();
							 break;
					case 4 : PotionPosn = SpawninChamber4();
							 break;
					case 5 : PotionPosn = SpawninChamber5();
							 break;
			       default: break;
			}	
		while(SameBefore(PosnArray,PotionPosn,t-1)){
				delete PotionPosn;
			    PotionPosn = new posn;
				PotionChamberNum = randNumBtw(1,5);
				switch (PotionChamberNum) {
						case 1 : PotionPosn = SpawninChamber1();
							     break;
						case 2 : PotionPosn = SpawninChamber2();
							     break;
						case 3 : PotionPosn = SpawninChamber3();
							     break;
						case 4 : PotionPosn = SpawninChamber4();
							     break;
						case 5 : PotionPosn = SpawninChamber5();
							     break;
						default: break;	
						}
		}
						PotionPosn->c = genPotion();
						PosnArray[t] = PotionPosn;
						t++;
	}
	int n = 32;
	while(n < 42){
		posn *GoldPosn = new posn;
		int GoldChamberNum;
		GoldChamberNum = randNumBtw(1,5);
		switch (GoldChamberNum) {
				case 1 : GoldPosn = SpawninChamber1();
						 break;
				case 2 : GoldPosn = SpawninChamber2();
						 break;
				case 3 : GoldPosn = SpawninChamber3();
					     break;
				case 4 : GoldPosn = SpawninChamber4();
						 break;
				case 5 : GoldPosn = SpawninChamber5();
						 break;
				default: break;
				}	
		while(SameBefore(PosnArray,GoldPosn,n-1)){
				delete GoldPosn;
				GoldPosn = new posn;
			    GoldChamberNum = randNumBtw(1,5);
				switch (GoldChamberNum) {
						case 1 : GoldPosn = SpawninChamber1();
								 break;
						case 2 : GoldPosn = SpawninChamber2();
								 break;
						case 3 : GoldPosn = SpawninChamber3();
								 break;
						case 4 : GoldPosn = SpawninChamber4();
								 break;
						case 5 : GoldPosn = SpawninChamber5();
								 break;
						default: break;	
							}
			}
		 GoldPosn->c = genGold();
		 PosnArray[n] = GoldPosn;
		 n++;
	}
	return PosnArray;
}

posn** SetDragon(posn** PosnArray){
	int size = 0;
	for(int index=31;index < 42;index++){
		if(PosnArray[index]->c == 'S'){
			size++;
		}
	}

	if(size==0) return 0;
	posn* *DragonArray = new posn*[size+1];
	posn * sizeEle = new posn;
	sizeEle->x=size;
	sizeEle->y=size;
	sizeEle->c=' ';
	DragonArray[0]=sizeEle;

	int i=32;
	int t=1;
	while( i <= 41){
		if(PosnArray[i]->c == 'S'){
			int gold_x=PosnArray[i]->x;
			int gold_y=PosnArray[i]->y;
			posn *DragonPosn = new posn;
			int DragonNum;
			DragonNum = randNumBtw(1,8);
			switch(DragonNum) {
				case 1 : DragonPosn->x = gold_x - 1;
					     DragonPosn->y = gold_y + 1; 
					     break;
				case 2 : DragonPosn->x = gold_x - 1;
					     DragonPosn->y = gold_y;
						 break;
				case 3 : DragonPosn->x = gold_x - 1;
					     DragonPosn->y = gold_y - 1;
						 break;
				case 4 : DragonPosn->x = gold_x;
						 DragonPosn->y = gold_y - 1;
						 break;
				case 5 : DragonPosn->x = gold_x;
						 DragonPosn->y = gold_y + 1;
					     break;
				case 6 : DragonPosn->x = gold_x + 1;
						 DragonPosn->y = gold_y - 1;
						 break;
				case 7 : DragonPosn->x = gold_x + 1;
					     DragonPosn->y = gold_y;
					     break;
				case 8 : DragonPosn->x = gold_x + 1;
					     DragonPosn->y = gold_y + 1;
						 break;
				default: break;
						}
						DragonPosn->c = 'D';
			while(SameBefore(PosnArray,DragonPosn,42) || SameBefore(DragonArray,DragonPosn,t) || inChamber(DragonPosn) == false){
				delete DragonPosn;
				DragonPosn = new posn;
				DragonNum = randNumBtw(1,8);
				switch(DragonNum) {
					case 1 : DragonPosn->x = gold_x - 1;
							 DragonPosn->y = gold_y + 1; 
						     break;
					case 2 : DragonPosn->x = gold_x - 1;
							 DragonPosn->y = gold_y;
							 break;
					case 3 : DragonPosn->x = gold_x - 1;
							 DragonPosn->y = gold_y - 1;
							 break;
					case 4 : DragonPosn->x = gold_x;
							 DragonPosn->y = gold_y - 1;
							 break;
					case 5 : DragonPosn->x = gold_x;
							 DragonPosn->y = gold_y + 1;
							 break;
					case 6 : DragonPosn->x = gold_x + 1;
							 DragonPosn->y = gold_y - 1;
						     break;
					case 7 : DragonPosn->x = gold_x + 1;
						     DragonPosn->y = gold_y;
							 break;
					case 8 : DragonPosn->x = gold_x + 1;
							 DragonPosn->y = gold_y + 1;
							 break;
					default: break;
					}
					DragonPosn->c = 'D';
					}
					DragonArray[t] = DragonPosn;
					t++;
					}
		i++;
	}
	return DragonArray;
}
		
											