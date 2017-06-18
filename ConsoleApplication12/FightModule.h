#include"BasicsForFight.h"
#include<Windows.h>
#include<mmsystem.h>
#pragma once

//function for damage by tower to enemy 
void DamageTowerToEnemy(Tower T, ListE* List1, ListE* List2, int Ticks);

//function for enemies attacking towers
void DamageEnemyToTower(Tower &T, ListE* List1, ListE* List2, int Ticks);

//function handling towers and enemies attacking each others
void Fight(castle &C, ListE* Active[], int Ticks);

//function to handle paving 
void Paving(NodeE* ptr, Tower &T);

//function to move enemies
void MoveEnemies(castle C, ListE* Active[]);

//function to count total enemies killed in each region every timestep
void SumTotalKilled(int KilledTimeStep[], int Killed[]);