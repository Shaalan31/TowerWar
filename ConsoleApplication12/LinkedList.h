#include"Queue.h"
#pragma once

//A struct that defines a list
struct ListE
{
	NodeE* Head;
	NodeE* Tail;
	int count;
};

//function to implement List
ListE* Createlist();

// function to insert at end of list
void InsertAtEnd(ListE* Enemies, enemy* E);

//function to destroy list of killed enemies
void Destroy(ListE* Killed);

//function to ensure that a list is not empty
bool EnemiesNotEmpty(ListE* Enemies);

//Implementing an array of pointers to the 8 Linked Lists 
ListE** ActiveList();

//function to check if all active lists are empty
bool EmptyActiveList(ListE* x[]);

//merges shielded list B into shielded list A and leaves list B empty
void MergeListSHLD(ListE* A, ListE* B);

////merges non-shielded list B into non-shielded list A and leaves list B empty
void MergeListOTHERS(ListE* A, ListE* B);

//function to check if all active lists are empty 
bool ArrayNotEmpty(ListE* Active[]);

//function to delete killed enemies & insert them into a linked list of killed enemies
void DeleteKilled(ListE* Active[], ListE* Killed, int KilledTimeStep[]);

//function to swap 2 enemies in a list
void SwapEnemies(enemy *&A, enemy *&B);

//function to sort a linked list according to enemies' prioritiess
void BubbleDes(ListE* Active);

//function to sort a linked list according to enemies' prioritiess
void BubbleAsc(ListE* Active);

//function to sort according to enemy fight delay 
void Sorting_FD(ListE* Active);


