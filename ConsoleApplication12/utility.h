#include <iostream>
using namespace std;

#include <windows.h>

//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

//Enemy types: Paver, Fighter, and Shielded Fighter
enum Etype {
	PVR,
	FITR,
	SHLD_FITR
};



//constants
#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3

#define EnemyShape		219  //ASCII code of enemy char shape 



//Tower
struct Tower
{
	int TW; //Tower width
	int TL; //Tower Height
	float Health;
	REGION RegionT;  //Region of the tower
	int Tower_Fire_power; //Tower fire power
	int No_Enemies;  //Number of enemies everytower can attack
	int UnpavedDistance;  // paved distance
	float InitialHealth;  //initial health of the tower
};


struct castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;	//width
	int L;  //Height
	Tower towers[4];	//Castle has 4 towers
	float C1, C2, C3;  // fight constants
};


struct enemy
{
	int ID;			//Each enemy has a unique ID (sequence number)
	REGION Region;	//Region of this enemy
	int Distance;	//Distance to the castle
	float Health;	//Enemy health
	Etype Type;		//PVR, FITR, SHLD_FITR
	int Enemy_Fire_Power;  //fire power of an enemy
	int Enemy_Reload_Period;  //reload period
	int Enemy_TimeStamp;    //The time when the enemy will appear
	int Enemy_Damage_Constant;  // The constant of damage (k)
	float priority;  //the constant of enemy pirority 
	bool isShot;  //determine if enemy is shot or not
	int FirstShot; //the time when an enemy is first shot
	float DC; //Defensive constant ( 1/k)
	bool AllowedToPave; //True if the enemy is allowed to pave
	int Pave; 
	int TimeKilled;//the time when an enemy is killed.
	int Enemy_Fight_Delay; //the time elapsed until an enemy is first shot by a tower
};

//Functions Prototype

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the game specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

/*A function to partition the castle into regions (A,B,C,D)*/
void DrawRegions(const castle & C);

/*A function to draw the castle and the towers*/
void DrawCastle(const castle & C,int SimulationTime);

/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(const enemy& E, int Ypos=0);

/*A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing*/
void DrawEnemies(enemy* enemies[],int size);

/*Student use this function to print his/her message*/
void PrintMsg(char*msg);

