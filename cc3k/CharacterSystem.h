#ifndef _CHARACTERSYSTEM_H_
#define _CHARACTERSYSTEM_H_
#include <iostream>
#include "randomNum.h"
#include "MapDisplay.h"

using namespace std;



class Character{

public:	
	int getHPMax(){return _hpMax;}
	int getHP(){return _hp;}
	int getAtk(){return _atk;}
	int getDef(){return _def;}
	int getGold(){return _gold;}
	int getAccuracy(){return _accuracy;}

	void setHPMax(int hpMax){_hpMax=hpMax;}
	void setHP(int hp){_hp=hp;}
	void setAtk(int atk){_atk=atk;}
	void setDef(int def){_def=def;}
	void setGold(int gold){_gold=gold;}
	void setAccuracy(int accu){_accuracy=accu;}
	
	Character(char c,string type);
	string getRace(){return _race;}
	void setRace(string race){_race=race;}
private:
	string _race;
	string _type;
	int _abilityId;
	int _hpMax;
	int _hp;
	int _atk;
	int _def;
	int _gold;
	int _accuracy;
};


//synchronize mapDisplay
void synchronizeStatus(Character*,DungeonMap*);


#endif

/* Test
#include <iostream>
#include "CharacterSystem.h"
using namespace std;

int main()
{
	Character *p;
	// PC character constructor tests
		p=new Character('h',"PC");
		p=new Character('o',"PC");
		p=new Character('d',"PC");
		p=new Character('e',"PC");
	// Enemy Character coustructor tests
		p=new Character('d',"Enemy");
		p=new Character('w',"Enemy");
		p=new Character('v',"Enemy");
		p=new Character('n',"Enemy");
		p=new Character('t',"Enemy");
		p=new Character('x',"Enemy");
		p=new Character('m',"Enemy");
	// Negtive Test
		p=new Character('@',"Enemy");
		p=new Character('@',"PC");																																																																								
	int i;
	cin>>i;
	return 0;
}
*/