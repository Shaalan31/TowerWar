#include"FinalizingGame.h"

//function to check if all towers are dead
bool TowersAreDead(castle C)
{
	if (C.towers[0].Health <= 0 && C.towers[1].Health <= 0 && C.towers[2].Health <= 0 && C.towers[3].Health <= 0)
		return true;
	return false;
}

//function to determine if game is win or loss
bool GameResult(castle C, ListE* Active[], QueueE* InActive)
{
	if (TowersAreDead(C))
	{
		cout << "Game is LOSS" << endl;
		return false;
	}
	if (EmptyActiveList(Active) && !Qnotempty(InActive))
	{
		cout << "Game is WIN" << endl;
		return false;
	}
	return true;
}