#pragma warning(disable: 4996)


/*
#include "stdafx.h"
#include <iostream>
#include "Cell.h"
#include "Grid.h"
using namespace std;

int main()
{
	DungeonMap* map=new DungeonMap;
	//case 'v':case 'w':case 'n':case 'm':case 'x':case 't':
	Cell * playerCell = new Cell(3,4,"PC",'h',map);
	Cell * enemyCell = new Cell(-1,-1,"Enemy",'n',map);
	synchronizeStatus(playerCell->getCharacter(),map);
	Cell * itemCell = new Cell(-1,-1,"Item",'G',map);
	Grid * grid = new Grid(1);
	map->printMap();
	// Test one: player use item
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"Test one: player use item"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	
	playerCell->action(itemCell);
	playerCell->action(itemCell);
	map->printMap();
	// Test two: player atk enemy
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"Test two: player atk enemy"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	playerCell->action(enemyCell);
	map->printMap();
	// Test three: enemy atk player
	
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"Test three: enemy atk player"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	enemyCell->action(playerCell);
	map->printMap();
	
	playerCell->action(enemyCell);
	map->printMap();
	int i;
	cin>>i;
	return 0;
}
*/


#include "stdafx.h"
#include <iostream>
#include "Grid.h"
#include "Cell.h"
#include <string>
using namespace std;

int FloorNum;
Grid *theGrid;
string command;
bool haveSetPlayer;

int DirectionToInt(string s){
	if (s == "no") return no;
	else if (s == "so") return so;
	else if (s == "ea") return ea;
	else if (s == "we") return we;
	else if (s == "ne") return ne;
	else if (s == "nw") return nw;
	else if (s == "se") return se;
	else if (s == "sw") return sw;
	else return 0;
}

int AttackToInt(string s){
	if (s == "ano") return no;
	else if (s == "aso") return so;
	else if (s == "aea") return ea;
	else if (s == "awe") return we;
	else if (s == "ane") return ne;
	else if (s == "anw") return nw;
	else if (s == "ase") return se;
	else if (s == "asw") return sw;
	else return 0;
}

int PotionToInt(string s){
	if (s == "uno") return no;
	else if (s == "uso") return so;
	else if (s == "uea") return ea;
	else if (s == "uwe") return we;
	else if (s == "une") return ne;
	else if (s == "unw") return nw;
	else if (s == "use") return se;
	else if (s == "usw") return sw;
	else return 0;
}

void CheckMove(string s){
	
	if(haveSetPlayer == false){
		cout<<"Hint:You should set your player before move it."<<endl;
		}
	else{
		int moveResult;
		int DirectionInteger = DirectionToInt(s);
	    moveResult = theGrid->playerMove(DirectionInteger);
	    if(moveResult == 0){
		cout<<"Invalid Command!"<<endl;
	    }
	    else if(moveResult == 1){
		theGrid->changeState();
		theGrid->printMap();

	}
	}
}

void CheckAttack(string s){
	int AttackDirection = AttackToInt(s);
	if(theGrid->playerAttack(AttackDirection) == true){
		theGrid->changeState();
		theGrid->printMap();
	}
}
void CheckUse(string s){
	int Direction = PotionToInt(s);
	if(theGrid->playerUsePotion(Direction) == true){
		theGrid->changeState();
		theGrid->printMap();
	}
}

void printLogo(){
	cout<<"******************************************************************************"<<endl;
	cout<<"                                                                              "<<endl;
	cout<<"                                                                              "<<endl;
	cout<<"          CCCCC           CCCCC          33333         K   K                  "<<endl;
	cout<<"        CC              CC                   3         K K                    "<<endl;
	cout<<"       C               C                 33333         K                      "<<endl;
	cout<<"        CC              CC                   3         K K                    "<<endl;
	cout<<"          CCCCC           CCCCC          33333         K   K                  "<<endl;
	cout<<"                                                                              "<<endl;
	cout<<"                                                  by Tangrui Song & Jing Zhang"<<endl;
	cout<<"                                                                              "<<endl;
	cout<<"******************************************************************************"<<endl;
	cout<<"                    Press Enter to start game!"<<endl;
	string s;
	getline(cin,s);
}

int main(){
	theGrid=new Grid(1);
	FloorNum = 1;
	haveSetPlayer = false;
	SetSeed();
	bool beenDead = false;
	start:
	printLogo();
	cout<<"please set your player:(h,e,o,d)"<<endl;
	while(1){
		cout<<"Command: ";
		getline(cin,command);
		if(cin.fail()) break;
		// set player
			if(command == "r"){
				FloorNum = 1;
				theGrid = new Grid(FloorNum);
				haveSetPlayer = false;
				cout<<"please set your player:(h,e,o,d)"<<endl;
				beenDead =false;
			}
			else if(beenDead==true) continue;
		    else if(command == "h"){
				if(haveSetPlayer == true){
					cout<<"You have set your player."<<endl;
				}
			else{
			    haveSetPlayer = true;
				theGrid->ChangeRace('h');
			    theGrid->printMap();
			}
		}
		    else if(command == "e"){
			if(haveSetPlayer == true) {
				cout<<"You have set your player."<<endl;
			}
			else{
				haveSetPlayer = true;
				theGrid->ChangeRace('e');
				theGrid->printMap();
			}
		}
			// test
			 else if(command == "*"){
			if(haveSetPlayer == true) {
				cout<<"You have set your player."<<endl;
			}
			else{
				haveSetPlayer = true;
				theGrid->ChangeRace('*');
				theGrid->printMap();
			}
		}
			 //test
			else if(command == "d"){
				if(haveSetPlayer == true){
					cout<<"You have set your player."<<endl;
				}
				else{
				haveSetPlayer = true;
				theGrid->ChangeRace('d');
				theGrid->printMap();
				}
			}
			else if(command == "o"){
				if(haveSetPlayer == true){
					cout<<"You have set your player."<<endl;
				}
				else{
				haveSetPlayer = true;
				theGrid->ChangeRace('o');
				theGrid->printMap();
				
				}
			}
		//move the player	
			else if(command == "no"){
				CheckMove("no");
			}
			else if(command == "so"){
				CheckMove("so");
			}
			else if(command == "ea"){ 
				CheckMove("ea");
			}
			//special case: consider about the stair;
		    else if(command == "we"){
			   if(haveSetPlayer == false){
				 cout<<"Hint:You should set your player before move it."<<endl;
				}
			  else{
				int result;
				result = theGrid->playerMove(we);
				if(result == 2){
					Cell *player = theGrid->getPlayer();
					FloorNum++;
					if(FloorNum >= 11){
						cout << "Congrats! You Win!"<<endl;
						cout << "Score: " << theGrid->score() <<endl;
						goto start;
						break;
					}
					theGrid = new Grid(FloorNum);
					theGrid->setPlayer(player);
					theGrid->printMap();
				}
				else if(result == 0){
					cout<<"Invalid Command!"<<endl;
					}
			    else if(result == 1){
					theGrid->changeState();
					theGrid->printMap();
					if(theGrid->checkPlayerDeath()){
						cout<<"Dead! You lost!"<<endl;
						cout << "Score: " << theGrid->score() <<endl;
					}
			}
			}
		}
		    else if(command == "ne"){
			    CheckMove("ne");
			}
		    else if(command == "nw"){
			    CheckMove("nw");
		    }
		    else if(command == "se"){
               CheckMove("se");
		    }
	        else if(command == "sw"){
               CheckMove("sw");
	        }
	        else if(command == "uno"){
				CheckUse("uno");
			}
			else if(command == "uso"){
				CheckUse("uso");
			}
			else if(command == "uea"){
				CheckUse("uea");
			}
			else if(command == "uwe"){
				CheckUse("uwe");
			}
			else if(command == "une"){
				CheckUse("une");
		    }
			else if(command == "unw"){
				CheckUse("unw");
			}
			else if(command == "use"){
				CheckUse("use");
			}
		    else if(command == "usw"){
			    CheckUse("usw");
		    }
		    else if(command == "ano"){
				CheckAttack("ano");
			}
			else if(command == "aso"){
				CheckAttack("aso");
			}
			else if(command == "aea"){
				CheckAttack("aea");
			}
			else if(command == "awe"){
				CheckAttack("awe");
			}
			else if(command == "ane"){
				CheckAttack("ane");
			}
			else if(command == "anw"){
				CheckAttack("anw");
			}
			else if(command == "ase"){
				CheckAttack("ase");
			}
			else if(command == "asw"){
				CheckAttack("asw");
			}

			else if(command =="q"){
				cout<<"Quit Game!"<<endl;
				return 0;
			}
			else{
				cout<<"invalid command"<<endl;
			}

		if(theGrid->checkPlayerDeath()){
		cout<<"Dead! You lost!"<<endl;
		cout << "Score: " << theGrid->score() <<endl;
		cout<<"Press r to restart the game!"<<endl;
		}
	}
	return 0;
}
			
				
				
			
		
		
				
				
				