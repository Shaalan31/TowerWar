#include"utility.h"
#pragma once

struct NodeE
{
	enemy *data;
	NodeE *next;
};

//A struct that defines a Queue
struct QueueE
{
	NodeE* front;
	NodeE* rear;
	int count;
};

//function to implement Queue
QueueE* CreateQ();


//function that inserts an enemy in a Queue
void Enque(QueueE* Q, NodeE* E);

//function overload
void Enque(QueueE* Q, enemy* info);

//function that deletes an enemy from the queue and return it back to you
bool Deque(QueueE* Q, enemy* &data);

//function to read the first node in the Queue without deleting it
NodeE* QTop(QueueE* Q);

//function to check if Queue is empty
bool Qnotempty(QueueE* Q);
