#include"FinalizingGame.h"
#pragma once

//function to determine the region where the enemy will be spawned
int whichRegion(castle C, REGION X);

/*
0- SHLD A
1- Others A
2- SHLD B
3- Others B
4- SHLD C
5- Others C
6- SHLD D
7- Others D
*/
//function to activate enemies from the Queue of inactive enemies to the active lists
void spawn(castle C, QueueE* Inactive, ListE* Active[], int Ticks);

//function to merge lists if a tower is destroyed
void MergeIfDestroyed(castle C, ListE* Active[]);

//function to change region of an Enemy 
void ChangeRegion(ListE* enemy, REGION R);

//function to send enemies from their region to the adjacent region if a tower is dead 
void sendToNext(castle C, ListE* Active[], REGION R);

//Assigning speed to an Enemy
int DifferentSpeed(NodeE* enemy);

//function to move active enemies of an active list
void MiniMoving(Tower T, ListE* List);

//function to set priorities to shielded enemies 
void SetPirority(ListE* Active[], castle C, int Ticks);

//function to calculate the remaining time for an enemy to shoot
int EnemyRemainingTimeToShoot(NodeE* E, int ticks);

//function to check if Enemy is allowed to Fire
bool isAllowedToFire(NodeE*E, int Ticks);

//function to calculate the priority for each shielded enemy 
float EnemyPriority(NodeE* E, int ticks, castle Z);

//function to calculate damage of an enemy to tower
float EnemyDamage2Tower(NodeE* fighter);

//function to calculate damage of a tower to enemy
float TowerDamage2Enemy(Tower T, NodeE* fighter);

//function to check if a paver is allowed to pave
bool isAllowedToPave(NodeE* paver, int Distance);