#include"PrintOutputFile.h"
#include<fstream>

//function to print info about killed enemies each time step 
void MajorOutput(ListE* killed, int &S, int &TotalFD, int &TotalKD, ofstream &output_f)
{
	NodeE*ptr = killed->Head;
	while (ptr)
	{
		TotalFD += (ptr->data->FirstShot - ptr->data->Enemy_TimeStamp);
		TotalKD += (ptr->data->TimeKilled - ptr->data->FirstShot);
		output_f << ptr->data->TimeKilled << "		" << S << "		" << (ptr->data->FirstShot - ptr->data->Enemy_TimeStamp) << "	 " << (ptr->data->TimeKilled - ptr->data->FirstShot) << "	  " << (ptr->data->TimeKilled - ptr->data->Enemy_TimeStamp);
		output_f << endl;
		ptr = ptr->next;
		S++;
	}
}