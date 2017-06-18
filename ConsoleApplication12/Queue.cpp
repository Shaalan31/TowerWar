#include"Queue.h"

//A struct that defines the node of an Enemy
/*struct NodeE
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
};*/

//function to implement Queue
QueueE* CreateQ()
{
	QueueE* Q = new QueueE;
	Q->front = NULL;
	Q->rear = NULL;
	Q->count = 0;
	return Q;
}

//function that inserts an enemy in a Queue
void Enque(QueueE* Q, NodeE* E)
{
	E->next = NULL;
	if (Q->front == NULL)
	{
		Q->front = E;
		Q->rear = E;
		Q->count++;
		return;
	}
	Q->rear->next = E;
	Q->count++;
	Q->rear = E;
}

//function overload
void Enque(QueueE* Q, enemy* info)
{
	NodeE *E = new NodeE;
	E->data = info;
	E->next = NULL;
	if (Q->front == NULL)
	{
		Q->front = E;
		Q->rear = E;
		return;
	}
	Q->rear->next = E;
	Q->rear = E;
}

//function that deletes an enemy from the queue and return it back to you
bool Deque(QueueE* Q, enemy* &data)
{
	if (Q->front == NULL)
		return false;
	NodeE* temp = Q->front;
	Q->front = Q->front->next;
	data = temp->data;
	if (Q->front == NULL)
		Q->rear = Q->front;
	delete temp;
	return true;
}

//function to read the first node in the Queue without deleting it
NodeE* QTop(QueueE* Q)
{
	NodeE* top;
	top = Q->front;
	return top;
}

//function to check if Queue is empty
bool Qnotempty(QueueE* Q)
{
	if (Q->front == NULL)
		return false;

	return true;
}
