#include"edits.h"
#include<time.h>
int main()
{
	int start = time(0);
	cout << "Welcome to the game, You can choose one of the 3 modes" << endl << "1- Interactive mode";
	cout << endl << "2- Step-by-step mode" << endl << "3- Silent mode   ";
		//Try the 3 sample input files by changing the parameter in the SimpleSimulator to Sample1, Sample2, or Sample3.
	int x;
	
	cin >> x;
	AdvancedSimulator("Sample100.txt",x);
	int end = time(0);
	cout << "Time consumed = " << end - start;
	system("pause");
}