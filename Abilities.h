/*
#ifndef _ABILITIES_H_
#define _ABILITIES_H_
#include "CharacterSystem.h"

const int NUM_OF_ABILITIES=3;

void(*skillSet[NUM_OF_ABILITIES])(CharacterSystem*,CharacterSystem*)={DoubleGold,PositiveEffect,HalfGold};

enum ABILITYID{
	dbGold,posEff,hfGold
};


//AbilityId: 0
// dwarf: gold is double in value
void DoubleGold(CharacterSystem* atker,CharacterSystem* defer);

//AbilityId: 1
// elves: negative potion have positive effects
void PositiveEffect(CharacterSystem* atker,CharacterSystem* defer);

//AbilityId: 2
// orc: gold is half in value
void HalfGold(CharacterSystem* atker,CharacterSystem* defer);

#endif
*/