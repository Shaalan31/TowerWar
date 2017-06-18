#include"FightModule.h"

//function for damage by tower to enemy 
void DamageTowerToEnemy(Tower T, ListE* List1, ListE* List2, int Ticks)
{
	NodeE* ptr1 = List1->Head;
	NodeE*ptr2 = List2->Head;
	int NoEnemiesShot = 0;
	if (EnemiesNotEmpty(List1))
	{
		while (ptr1 && NoEnemiesShot <= T.No_Enemies)
		{
			ptr1->data->Health -= TowerDamage2Enemy(T, ptr1);
			NoEnemiesShot++;

			if (ptr1->data->isShot == false)
			{
				ptr1->data->isShot = true;
				ptr1->data->FirstShot = Ticks;
			}
			if (ptr1->data->Health <= 0)
			{
				ptr1->data->TimeKilled = Ticks;
				ptr1->data->Enemy_Fight_Delay = (ptr1->data->FirstShot) - (ptr1->data->Enemy_TimeStamp);
			}
			ptr1 = ptr1->next;
		}
	}
	else if (EnemiesNotEmpty(List2))
	{
		while (ptr2 && NoEnemiesShot <= T.No_Enemies)
		{
			ptr2->data->Health -= TowerDamage2Enemy(T, ptr2);
			NoEnemiesShot++;

			if (ptr2->data->isShot == false)
			{
				ptr2->data->isShot = true;
				ptr2->data->FirstShot = Ticks;
			}
			if (ptr2->data->Health <= 0)
			{
				ptr2->data->TimeKilled = Ticks;
				ptr2->data->Enemy_Fight_Delay = (ptr2->data->FirstShot) - (ptr2->data->Enemy_TimeStamp);
			}
			ptr2 = ptr2->next;
		}
	}
	else
	{
		return;
	}
}

//function for enemies attacking towers
void DamageEnemyToTower(Tower &T, ListE* List1, ListE* List2, int Ticks)
{
	NodeE* ptr1 = List1->Head;
	NodeE*ptr2 = List2->Head;
	if (EnemiesNotEmpty(List1))
	{
		while (ptr1)
		{
			if (ptr1->data->Health > 0 && isAllowedToFire(ptr1, Ticks))
			{
				T.Health -= EnemyDamage2Tower(ptr1);
			}
			ptr1 = ptr1->next;
			if (T.Health <= 0)
			{
				PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);
				T.Health = 0;
				return;
			}
		}
	}
	if (EnemiesNotEmpty(List2))
	{
		while (ptr2)
		{
			if (ptr2->data->Type == 0)
			{
				Paving(ptr2, T);
			}
			else if (ptr2->data->Type != 0 && ptr2->data->Health > 0 && isAllowedToFire(ptr2, Ticks))
			{
				T.Health -= EnemyDamage2Tower(ptr2);
			}
			ptr2 = ptr2->next;
			if (T.Health <= 0)
			{
				PlaySound(TEXT("sound.wav"), NULL, SND_SYNC);
				T.Health = 0;
				return;
			}
		}
	}
	else
		return;
}

//function handling towers and enemies attacking each others
void Fight(castle &C, ListE* Active[], int Ticks)
{
	DamageTowerToEnemy(C.towers[0], Active[0], Active[1], Ticks);
	DamageTowerToEnemy(C.towers[1], Active[2], Active[3], Ticks);
	DamageTowerToEnemy(C.towers[2], Active[4], Active[5], Ticks);
	DamageTowerToEnemy(C.towers[3], Active[6], Active[7], Ticks);

	DamageEnemyToTower(C.towers[0], Active[0], Active[1], Ticks);
	DamageEnemyToTower(C.towers[1], Active[2], Active[3], Ticks);
	DamageEnemyToTower(C.towers[2], Active[4], Active[5], Ticks);
	DamageEnemyToTower(C.towers[3], Active[6], Active[7], Ticks);
}

//function to handle paving 
void Paving(NodeE* ptr, Tower &T)
{
	if (isAllowedToPave(ptr, T.UnpavedDistance) && T.UnpavedDistance != 2)
	{
		T.UnpavedDistance = (ptr->data->Distance) - (ptr->data->Enemy_Fire_Power);
		if (T.UnpavedDistance < 2)
			T.UnpavedDistance = 2;
	}
}

//function to move enemies
void MoveEnemies(castle C, ListE* Active[])
{
	MiniMoving(C.towers[0], Active[0]);
	MiniMoving(C.towers[0], Active[1]);
	MiniMoving(C.towers[1], Active[2]);
	MiniMoving(C.towers[1], Active[3]);
	MiniMoving(C.towers[2], Active[4]);
	MiniMoving(C.towers[2], Active[5]);
	MiniMoving(C.towers[3], Active[6]);
	MiniMoving(C.towers[3], Active[7]);
}

//function to count total enemies killed in each region every timestep
void SumTotalKilled(int KilledTimeStep[], int Killed[])
{
	for (int i = 0; i < 4; i++)
	{
		Killed[i] += KilledTimeStep[i];
	}
}