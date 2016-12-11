#ifndef _RANDOMNUM_H_
#define _RANDOMNUM_H_
#include <cstdlib>
#include <ctime>

struct posn{
	char c;
	int x;
	int y;
};

int randNumBtw(int low,int high);
char genEnemy();// V(ampire), W(erewolf), N(goblin), M(erchant), D(ragon),X(Phoenix), T(roll), M(erchant).
bool inBlock(posn item,int minX,int maxX,int minY,int maxY);
bool inChamber1(posn item);
bool inChamber2(posn item);
bool inChamber3(posn item);
bool inChamber4(posn item);
bool inChamber5(posn item);
posn** SetItem();
void SetSeed();

#endif

/* Test
#include <iostream>
#include "randomNum.h"
using namespace std;

int main()
{
	int j,h=0;
	for(int i=0;i<180;i++){
		if(genEnemy()=='m') h++;
	}
	posn x={19,75};
	cout<<inChamber5(x)<<endl;
	cin>>j;
	return 0;
}
*/

/* TEST !!
#include <iostream>
#include "randomNum.h"
using namespace std;

int main(){
	SetSeed();
	posn** test = new posn*[22];
	test = SetItem();
	for(int i=1;i<22;i++){
		cout<<test[i]->x<<endl;
		cout<<test[i]->y<<endl;
		cout<<test[i]->c<<endl;
	}
	int i;
	cin>>i;
	return 0;
}
*/