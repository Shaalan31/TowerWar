#include"AdvancedSimulator.h"
#include<fstream>

//function acting as a simulator to the game 
void AdvancedSimulator(char* s, int mode)
{
	//Needed Initializations
	ofstream output_f;
	output_f.open("Output File.txt", ios::out);
	output_f << "TimeStep" << "  " << "Sequence" << "  " << "Fight Delay" << "  " << "Kill Delay" << "  " << "Fight Time" << endl;
	int S = 1;
	int TotalFD = 0;
	int TotalKD = 0;
	int Ticks = 0;
	int NumKilled = 0;
	float C1 = 0, C2 = 0, C3 = 0;
	int TotalKilled[4];
	TotalKilled[0] = 0;
	TotalKilled[1] = 0;
	TotalKilled[2] = 0;
	TotalKilled[3] = 0;
	int KilledLastTime[4];
	KilledLastTime[0] = 0;
	KilledLastTime[1] = 0;
	KilledLastTime[2] = 0;
	KilledLastTime[3] = 0;
	int CurrentEnemies[4];
	CurrentEnemies[0] = 0;
	CurrentEnemies[1] = 0;
	CurrentEnemies[2] = 0;
	CurrentEnemies[3] = 0;

	//The Needed Declarations
	QueueE* Inactive = CreateQ();
	castle Castle;
	enemy* Inact2Act;

	//calling functions to create Queues for the Inactive,Active, and Killed Enemies 
	ListE** Active = ActiveList();
	ListE* killed = Createlist();
	bool GamePlaying = true;

	//Castle Initializations
	Castle.Xstrt = CastleXStrt;
	Castle.Ystrt = CastleYStrt;
	Castle.W = CastleWidth;
	Castle.L = CastleLength;

	int n;
	cin.get();
	loadfile(Inactive, s, Castle);
	enemy **X = new enemy*[Inactive->rear->data->ID];
	int TotalEnemies = Inactive->rear->data->ID;

	while (GamePlaying)
	{
		Ticks++;
		spawn(Castle, Inactive, Active, Ticks);
		SetPirority(Active, Castle, Ticks); //x
		BubbleDes(Active[0]);
		BubbleDes(Active[2]);
		BubbleDes(Active[4]);
		BubbleDes(Active[6]);
		n = Integrator(Active, X, CurrentEnemies);
		if (mode == 1)
		{
			SetWindow();
			DrawCastle(Castle, Ticks);
			DrawEnemies(X, n);
			cout << "Number of current enemies   A:" << CurrentEnemies[0] << "   B:" << CurrentEnemies[1] << "   C:" << CurrentEnemies[2] << "   D:" << CurrentEnemies[3] << endl;
			cout << "Number of enemies killed last time-step   A:" << KilledLastTime[0] << "   B:" << KilledLastTime[1] << "   C:" << KilledLastTime[2] << "   D:" << KilledLastTime[3] << endl;
			cout << "Total number of killed enemies   A:" << TotalKilled[0] << "   B:" << TotalKilled[1] << "   C:" << TotalKilled[2] << "   D:" << TotalKilled[3] << endl;
			cout << "Unpaved Distance in    A:" << Castle.towers[0].UnpavedDistance << "   B:" << Castle.towers[1].UnpavedDistance << "   C:" << Castle.towers[2].UnpavedDistance << "   D:" << Castle.towers[3].UnpavedDistance << endl;
			Sleep(1000);
		}
		else if (mode == 2)
		{
			SetWindow();
			DrawCastle(Castle, Ticks);
			DrawEnemies(X, n);
			cout << "Number of current enemies   A:" << CurrentEnemies[0] << "   B:" << CurrentEnemies[1] << "   C:" << CurrentEnemies[2] << "   D:" << CurrentEnemies[3] << endl;
			cout << "Number of enemies killed last time-step   A:" << KilledLastTime[0] << "   B:" << KilledLastTime[1] << "   C:" << KilledLastTime[2] << "   D:" << KilledLastTime[3] << endl;
			cout << "Total number of killed enemies   A:" << TotalKilled[0] << "   B:" << TotalKilled[1] << "   C:" << TotalKilled[2] << "   D:" << TotalKilled[3] << endl;
			cout << "Unpaved Distance in    A:" << Castle.towers[0].UnpavedDistance << "   B:" << Castle.towers[1].UnpavedDistance << "   C:" << Castle.towers[2].UnpavedDistance << "   D:" << Castle.towers[3].UnpavedDistance << endl;
			cin.get();
		}
		Fight(Castle, Active, Ticks);
		MergeIfDestroyed(Castle, Active);
		MoveEnemies(Castle, Active);
		DeleteKilled(Active, killed, KilledLastTime);
		SumTotalKilled(KilledLastTime, TotalKilled);
		GamePlaying = GameResult(Castle, Active, Inactive);
		Sorting_FD(killed);
		MajorOutput(killed, S, TotalFD, TotalKD, output_f);
		Destroy(killed);
	}
	output_f << "T1_Total_Damage" << "  " << "T2_Total_Damage" << "  " << "T3_Total_Damage" << "  " << "T4_Total_Damage";
	output_f << endl;
	output_f << (Castle.towers[0].InitialHealth - Castle.towers[0].Health) << "		" << (Castle.towers[1].InitialHealth - Castle.towers[1].Health) << "		" << (Castle.towers[2].InitialHealth - Castle.towers[2].Health) << "		  " << (Castle.towers[3].InitialHealth - Castle.towers[3].Health) << endl;
	output_f << "R1_Distance" << " " << "R2_Distance" << "  " << "R3_Distance" << "  " << "R4_Distance";
	output_f << endl;
	output_f << "    " << Castle.towers[0].UnpavedDistance << "		" << Castle.towers[1].UnpavedDistance << "		 " << Castle.towers[2].UnpavedDistance << "			" << Castle.towers[3].UnpavedDistance;
	output_f << endl;

	if (!TowersAreDead(Castle))
	{
		output_f << " Game is WIN ";
		output_f << endl;
		output_f << "Total Enemies   =" << TotalEnemies;
		output_f << endl;
		output_f << "Fight Delay Average = " << "  " << TotalFD / S;
		output_f << endl;
		output_f << "Kill Delay Average = " << "  " << TotalKD / S;
		output_f << endl;
	}
	else
	{
		output_f << " Game is LOSS ";
		output_f << endl;
		output_f << "Total Killed Enemies   =" << S;
		output_f << endl;
		output_f << "Total Alive Enemies  = " << "  " << TotalEnemies - S;
		output_f << endl;
		output_f << "Fight Delay Average  =" << "  " << TotalFD / S;
		output_f << endl;
		output_f << "Kill Delay Average  =" << "  " << TotalKD / S;
		output_f << endl;
	}
	output_f.close();
	for (int i = 0; i < TotalEnemies; i++)
		 X[i]=NULL;
	delete X;
}