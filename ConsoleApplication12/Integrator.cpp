#include"Integrator.h"

//function to create an array of pointers to all enemies of all regions 
int Integrator(ListE* Active[], enemy* Enemies[], int CurrentEnemies[])
{
	int n = 0;
	CurrentEnemies[0] = 0;
	CurrentEnemies[1] = 0;
	CurrentEnemies[2] = 0;
	CurrentEnemies[3] = 0;
	for (int i = 0; i < 8; i++)
	{
		int n1 = 0;
		NodeE* ptr = Active[i]->Head;
		while (ptr)
		{
			Enemies[n] = ptr->data;
			n++;
			n1++;
			ptr = ptr->next;
		}
		CurrentEnemies[i / 2] += n1;
	}
	return n;
}