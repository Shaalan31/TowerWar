#include"LoadFunction.h"
#include<fstream>

//Function to read input from text file
void loadfile(QueueE* Q, char *s, castle &C)
{
	ifstream myfile;
	myfile.open(s);
	int  N, TowerFirePower;
	float TowerHealth;
	myfile >> TowerHealth;
	myfile >> N;
	myfile >> TowerFirePower;

	// A loop to insert Tower data into an array ( array of structs )
	for (int i = 0; i < 4; i++)
	{
		C.towers[i].Health = TowerHealth;
		C.towers[i].No_Enemies = N;
		C.towers[i].Tower_Fire_power = TowerFirePower;
		C.towers[i].UnpavedDistance = 30;
		C.towers[i].RegionT = (REGION)i;
		C.towers[i].InitialHealth = TowerHealth;
	}
	myfile >> C.C1;
	myfile >> C.C2;
	myfile >> C.C3;

	int id, TimeStep, EnemyType, EnemyFirePower, EnemyReloadPeriod;
	float health;
	char region;
	
	//a loop for reading the input file until it's end
	while (!myfile.eof())
	{
		myfile >> id;
		if (id == -1)
			break;
		myfile >> EnemyType;
		myfile >> TimeStep;
		myfile >> health;
		myfile >> EnemyFirePower;
		myfile >> EnemyReloadPeriod;
		myfile >> region;

		//creating nodes where the Enemies will be input
		NodeE *temp = new NodeE;
		temp->data = new enemy;

		//reading enemies' data
		temp->data->ID = id;

		// intializing distance
		temp->data->Distance = 60;

		//intializing all enemies not yet shot
		temp->data->isShot = false;

		//if conditions for initializing Regions
		if (region == 'A')
			temp->data->Region = (REGION)0;
		else if (region == 'B')
			temp->data->Region = (REGION)1;
		else if (region == 'C')
			temp->data->Region = (REGION)2;
		else
			temp->data->Region = (REGION)3;

		// if conditions for initializing Enemy Types
		if (EnemyType == 0)
		{
			temp->data->Type = (Etype)0;
			temp->data->DC = 1;
		}

		if (EnemyType == 1)
		{
			temp->data->Type = (Etype)1;
			temp->data->DC = 1;
		}
		if (EnemyType == 2)
		{
			temp->data->Type = (Etype)2;
			temp->data->DC = 0.5;
		}

		temp->data->Enemy_TimeStamp = TimeStep;
		temp->data->Health = health;
		temp->data->Enemy_Fire_Power = EnemyFirePower;
		temp->data->Enemy_Reload_Period = EnemyReloadPeriod;

		//insert inactive enemy in a queue 
		Enque(Q, temp);
	}
}
