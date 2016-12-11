#include "stdafx.h"
#include "Cell.h"
#include <cmath>
#include <string>

//helper func
void Cell::testUse(Cell * inputCell){
		cout<<"************************************************"<<endl;
		cout<<"_character->getRace():"<<_character->getRace()<<endl;
		cout<<"_character->getHP():"<<_character->getHP()<<endl;
		cout<<"_character->getAtk():"<<_character->getAtk()<<endl;
		cout<<"_character->getDef():"<<_character->getDef()<<endl;
		cout<<"************************************************"<<endl;
		if(inputCell!=0){
		cout<<"************************************************"<<endl;
		cout<<"inputCell: getRace():"<<inputCell->_character->getRace()<<endl;
		cout<<"inputCell: getHP():"<<inputCell->_character->getHP()<<endl;
		cout<<"inputCell: getAtk():"<<inputCell->_character->getAtk()<<endl;
		cout<<"inputCell: getDef():"<<inputCell->_character->getDef()<<endl;
		cout<<"************************************************"<<endl;		
		}
}
/*

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
*/

int damageCalc(int myAtk,int otherDef){
	float atk = myAtk;
	float def = otherDef;
	float damage;
	damage = ceil((100/(100+def))*atk);
	int damageRound = (int)damage;
	return damageRound;
}

Cell::Cell(int x,int y,string type,char identity,DungeonMap* map):_x(x),_y(y),_type(type),_identity(identity),_map(map),
	_movingDirection(randNumBtw(0,7)),_dead(false),_beenProtected(true),_dragonHordeCell(0),_hostile(true){
	if(type=="PC"){
		_character = new Character(identity,"PC");
		_item = 0;

	}
	else if(type=="Enemy"){
		_character = new Character(identity,"Enemy");
		_item = 0;		
	}else if(type=="Item"){
		_character=0;
		switch (identity)
		{
		case 'H':
			_item = new PotionRH(0,_map);
			break;
		case 'A':
			_item = new PotionBA(0,_map);
			break;
		case 'D':
			_item = new PotionBD(0,_map);
			break;
		case 'h':
			_item = new PotionPH(0,_map);
			break;
		case 'a':
			_item = new PotionWA(0,_map);
			break;
		case 'd':
			_item = new PotionWD(0,_map);
			break;
		case 'N':
			_item = new GoldN(0,_map);
			setBeenProtected(false);
			break;
		case 'S':
			_item = new GoldS(0,_map);
			setBeenProtected(false);
			break;
		case 'M':
			_item = new GoldM(0,_map);
			setBeenProtected(false);
			break;
		case 'G':
			_item = new GoldD(0,_map);
			break;
		default:
			cerr<<"Invalid 'identity' in Cell Constructor"<<endl;
			break;
		}
	}else if(type=="\\"){
		_item=0;
		_character=0;
	}else{
		cerr<<"Invalid type in Cell Constructor"<<endl;
	}
}

void Cell::action(Cell* inputTarget){
	if(_type=="Potion") return;
	if(inputTarget->getType()=="Item"){
		inputTarget->setItemUser(_character);
		//inputTarget->_item->setPlayer(_character);
		
		inputTarget->_item->useMe();
		inputTarget->_item->notifyDisplayMap();
		inputTarget->setDead(true);
		if(_character->getHP()<=0){
			setDead(true);
		}
	}else{
		int damage = damageCalc(_character->getAtk(),inputTarget->_character->getDef());
		//
		//Test
		testUse(inputTarget);
		cout<<"damage is "<<damage<<endl;
		//
		inputTarget->_character->setHP(inputTarget->_character->getHP()-damage);
		if (inputTarget->_character->getHP()<=0) {
			inputTarget->setDead(true);
			if(inputTarget->_character->getRace()!="merchant"&&inputTarget->_character->getRace()!="dragon")_character->setGold(_character->getGold()+1);
			if(getType()=="PC") synchronizeStatus(_character,_map);
		}
		string action=_map->getAction();
		action = _character->getAccuracy()==100?"PC":_character->getRace();
		action +=" deals";
		action += intToString(damage) +" dmg to ";
		action +=inputTarget->getCharacter()->getAccuracy()==100?"PC":inputTarget->getCharacter()->getRace();
		if(inputTarget->getType()=="PC") action+=".";
		else{
			action +="(";
			action+=intToString(inputTarget->getCharacter()->getHP())+"HP).";
		}

		if(inputTarget->getDead()) action +=inputTarget->_character->getRace()+" dies.";
		if(inputTarget->_character->getRace()!="merchant"&&inputTarget->_character->getRace()!="dragon") action+="Got 1 gold."; 
		_map->setAction(action);
		_map->statusRefresh();
		if(inputTarget->getType()=="PC") synchronizeStatus(inputTarget->_character,_map);
	}
}