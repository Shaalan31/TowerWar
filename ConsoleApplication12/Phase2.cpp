#include"AdvancedSimulator.h"

int main()
{
	cout << "Welcome to the game, You can choose one of the 3 modes" << endl << "1- Interactive mode";
	cout << endl << "2- Step-by-step mode" << endl << "3- Silent mode   ";
	//Try the 3 sample input files by changing the parameter in the SimpleSimulator to Sample100, Sample2, or Sample1.
	//The outputs are in the project file called Output100, Output1, and Output2 respectively 
	int x;

	cin >> x;
	AdvancedSimulator("Sample2.txt", x);
	
}