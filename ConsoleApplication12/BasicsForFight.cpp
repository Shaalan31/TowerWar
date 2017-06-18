#include"BasicsForFight.h"

//function to determine the region where the enemy will be spawned
int whichRegion(castle C, REGION X)
{
	int i = (int)X;
	int n = 0;
	while (C.towers[i % 4].Health <= 0)
	{
		i++;
		n++;
		if (n == 4)
			break;

	}

	return i % 4;

}

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
void spawn(castle C, QueueE* Inactive, ListE* Active[], int Ticks)
{

	enemy* Inact2Act;
	while (Qnotempty(Inactive))
	{
		if (QTop(Inactive)->data->Enemy_TimeStamp == Ticks)
		{
			Deque(Inactive, Inact2Act);
			int i = whichRegion(C, Inact2Act->Region);
			Inact2Act->Region = (REGION)i;
			if (Inact2Act->Type == 2)
				InsertAtEnd(Active[2 * i], Inact2Act);
			else
				InsertAtEnd(Active[2 * i + 1], Inact2Act);
		}
		else
			return;
	}
}

//function to merge lists if a tower is destroyed
void MergeIfDestroyed(castle C, ListE* Active[])
{
	sendToNext(C, Active, (REGION)0);
	sendToNext(C, Active, (REGION)1);
	sendToNext(C, Active, (REGION)2);
	sendToNext(C, Active, (REGION)3);
}

//function to change region of an Enemy 
void ChangeRegion(ListE* enemy, REGION R)
{
	NodeE* ptr = enemy->Head;
	while (ptr)
	{
		ptr->data->Region = R;
		ptr = ptr->next;
	}
}

//function to send enemies from their region to the adjacent region if a tower is dead 
void sendToNext(castle C, ListE* Active[], REGION R)
{
	if (C.towers[(int)R].Health > 0)
		return;
	int i = whichRegion(C, R);
	ChangeRegion(Active[2 * R], (REGION)i);
	ChangeRegion(Active[2 * R + 1], (REGION)i);
	MergeListSHLD(Active[2 * i], Active[2 * (int)R]);
	MergeListOTHERS(Active[2 * i + 1], Active[2 * (int)R + 1]);
}

//Assigning speed to an Enemy 
int DifferentSpeed(NodeE* enemy)
{
	if (enemy->data->Type == 0)
		return 1;
	int x = (int)enemy->data->Health / enemy->data->Enemy_Fire_Power;
	if (x > 8)
		return 8;
	return x + 1;
}

//function to move active enemies of an active list
void MiniMoving(Tower T, ListE* List)
{
	if (!EnemiesNotEmpty(List))
		return;
	NodeE*ptr = List->Head;
	while (ptr)
	{
		ptr->data->Distance -= DifferentSpeed(ptr);
		if (ptr->data->Distance < T.UnpavedDistance)
			ptr->data->Distance = T.UnpavedDistance;
		ptr = ptr->next;
	}
}

//function to set priorities to shielded enemies 
void SetPirority(ListE* Active[], castle C, int Ticks)
{
	for (int i = 0; i < 8; i += 2)
	{
		NodeE* ptr = Active[i]->Head;
		while (ptr)
		{
			ptr->data->priority = EnemyPriority(ptr, Ticks, C);
			ptr = ptr->next;
		}

	}
}

//function to calculate the remaining time for an enemy to shoot
int EnemyRemainingTimeToShoot(NodeE* E, int ticks)
{
	int x = E->data->Enemy_Reload_Period - ((ticks - E->data->Enemy_TimeStamp) % E->data->Enemy_Reload_Period);
	if (x == E->data->Enemy_Reload_Period)
		return 0;
	return x;
}

//function to check if Enemy is allowed to Fire
bool isAllowedToFire(NodeE*E, int Ticks)
{
	if (EnemyRemainingTimeToShoot(E, Ticks) == 0)
		return true;
	else
		return false;
}

//function to calculate the priority for each shielded enemy 
float EnemyPriority(NodeE* E, int ticks, castle Z)
{
	return (Z.C1*E->data->Enemy_Fire_Power / E->data->Distance) + (Z.C2 / (EnemyRemainingTimeToShoot(E, ticks) + 1) + (E->data->Health*Z.C3));
}

//function to calculate damage of an enemy to tower
float EnemyDamage2Tower(NodeE* fighter)
{
	if (fighter->data->Type == 0)
		return 0;
	else
		return (float)fighter->data->Enemy_Fire_Power / (float)fighter->data->Distance;
}

//function to calculate damage of a tower to enemy
float TowerDamage2Enemy(Tower T, NodeE* fighter)
{
	return (float)T.Tower_Fire_power*(fighter->data->DC / (float)fighter->data->Distance);

}

//function to check if a paver is allowed to pave
bool isAllowedToPave(NodeE* paver, int Distance)
{
	if (paver->data->AllowedToPave && ((paver->data->Distance) - Distance)<(paver->data->Enemy_Fire_Power))
	{
		paver->data->Pave = 0;
		paver->data->AllowedToPave = false;
		return true;
	}
	if (paver->data->Pave != paver->data->Enemy_Reload_Period)
		paver->data->Pave++;
	if (paver->data->Pave == paver->data->Enemy_Reload_Period)
		paver->data->AllowedToPave = true;
	return false;
}