#include"LinkedList.h"

//A struct that defines a list
/*struct ListE
{
	NodeE* Head;
	NodeE* Tail;
	int count;
};*/

//function to implement List
ListE* Createlist()
{
	ListE* Enemies = new ListE;
	Enemies->Head = NULL;
	Enemies->Tail = NULL;
	Enemies->count = 0;
	return Enemies;
}

// function to insert at end of list
void InsertAtEnd(ListE* Enemies, enemy* E)
{
	NodeE* AddedEnemy = new NodeE;
	AddedEnemy->next = NULL;
	AddedEnemy->data = E;
	if (Enemies->Head == NULL && Enemies->Tail == NULL)
	{
		Enemies->Head = AddedEnemy;
		Enemies->Tail = AddedEnemy;
		return;
	}
	Enemies->Tail->next = AddedEnemy;
	Enemies->Tail = AddedEnemy;
}

//function to destroy list of killed enemies
void Destroy(ListE* Killed)
{
	if (Killed->Head == NULL)
		return;
	NodeE*ptr = Killed->Head;
	NodeE* DeletedNode;
	while (ptr)
	{
		DeletedNode = ptr;
		ptr = ptr->next;
		delete DeletedNode;
	}
	Killed->Head = NULL;
	Killed->Tail = NULL;
}

//function to ensure that a list is not empty
bool EnemiesNotEmpty(ListE* Enemies)
{
	if (Enemies->Head == NULL)
		return false;
	else
		return true;

}

//Implementing an array of pointers to the 8 Linked Lists 
ListE** ActiveList()
{
	ListE** X;
	X = new ListE*[8];
	X[0] = Createlist();
	X[1] = Createlist();
	X[2] = Createlist();
	X[3] = Createlist();
	X[4] = Createlist();
	X[5] = Createlist();
	X[6] = Createlist();
	X[7] = Createlist();

	return X;
}

//function to check if all active lists are empty
bool EmptyActiveList(ListE* x[])
{
	int i = 0;
	for (int z = 0; z < 8; z++)
	{
		if (x[i]->Head == NULL)
			i++;
	}
	if (i == 8)
		return true;
	return false;
}

//merges shielded list B into shielded list A and leaves list B empty
void MergeListSHLD(ListE* A, ListE* B)
{
	if (B->Head == NULL)
		return;
	if (A->Head == NULL)
	{
		A->Head = B->Head;
		A->Tail = B->Tail;
		B->Tail = NULL;
		B->Head = NULL;
		BubbleDes(A);
		return;
	}
	A->Tail->next = B->Head;
	A->Tail = B->Tail;
	B->Tail = NULL;
	B->Head = NULL;
	BubbleDes(A);
	return;
}

////merges non-shielded list B into non-shielded list A and leaves list B empty
void MergeListOTHERS(ListE* A, ListE* B)
{
	if (B->Head == NULL)
		return;
	if (A->Head == NULL)
	{
		A->Head = B->Head;
		A->Tail = B->Tail;
		B->Tail = NULL;
		B->Head = NULL;
		BubbleAsc(A);
		return;
	}

	A->Tail->next = B->Head;
	A->Tail = B->Tail;
	B->Tail = NULL;
	B->Head = NULL;
	BubbleAsc(A);
	return;
}

//function to check if all active lists are empty 
bool ArrayNotEmpty(ListE* Active[])
{
	bool status = false;
	int i = 0;
	while (!status && i != 8)
	{
		if (Active[i]->Head == NULL)
			status = true;

		i++;
	}
	return status;
}

//function to delete killed enemies & insert them into a linked list of killed enemies
void DeleteKilled(ListE* Active[], ListE* Killed, int KilledTimeStep[])
{
	KilledTimeStep[0] = 0;
	KilledTimeStep[1] = 0;
	KilledTimeStep[2] = 0;
	KilledTimeStep[3] = 0;
	for (int i = 0; i < 8; i++)
	{
		NodeE* pre = Active[i]->Head;
		NodeE* KilledEnemy;
		while (pre && pre->data->Health <= 0)
		{
			KilledEnemy = pre;
			pre = KilledEnemy->next;
			InsertAtEnd(Killed, KilledEnemy->data);
			Active[i]->Head = pre;
			KilledTimeStep[i / 2]++;
			delete KilledEnemy;
		}
		if (pre == NULL)
			continue;
		if (pre->next != NULL)
		{
			while (pre->next != NULL)
			{
				if (pre->next->data->Health <= 0)
				{
					if (pre->next->next == NULL)
						Active[i]->Tail = pre;
					KilledEnemy = pre->next;
					pre->next = KilledEnemy->next;
					InsertAtEnd(Killed, KilledEnemy->data);
					KilledTimeStep[i / 2]++;
					delete KilledEnemy;
				}
				else
				{
					pre = pre->next;
				}
			}
		}
	}
}

//function to swap 2 enemies in a list
void SwapEnemies(enemy *&A, enemy *&B)
{
	enemy *temp = A;
	A = B;
	B = temp;
}

//function to sort a linked list according to enemies' prioritiess
void BubbleDes(ListE* Active)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		NodeE* ptr = Active->Head;
		while (ptr && ptr->next)
		{
			if (ptr->data->priority < ptr->next->data->priority)
			{
				SwapEnemies(ptr->data, ptr->next->data);
				swapped = true;
			}
			ptr = ptr->next;

		}
	}

}

//function to sort a linked list according to enemies' prioritiess
void BubbleAsc(ListE* Active)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		NodeE* ptr = Active->Head;
		while (ptr && ptr->next)
		{
			if (ptr->data->Enemy_TimeStamp > ptr->next->data->Enemy_TimeStamp)
			{
				SwapEnemies(ptr->data, ptr->next->data);
				swapped = true;
			}
			ptr = ptr->next;

		}
	}

}

//function to sort according to enemy fight delay 
void Sorting_FD(ListE* Active)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		NodeE* ptr = Active->Head;
		while (ptr && ptr->next)
		{
			if (ptr->data->Enemy_Fight_Delay > ptr->next->data->Enemy_Fight_Delay)
			{
				SwapEnemies(ptr->data, ptr->next->data);
				swapped = true;
			}
			ptr = ptr->next;
		}
	}
}


