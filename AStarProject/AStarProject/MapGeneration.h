
#include <iostream>
#include <fstream>

using namespace std;

const int MAXROOMSIZE = 10;


struct MapStorageYCoords
{
	char xCoordsChar[MAXROOMSIZE];
	int  xCoords[MAXROOMSIZE];
};
class GenerateMap
{
private:
	ifstream inp;
	ofstream ofp;
	int startLoc[2];
	int endLoc[2];
	MapStorageYCoords yCoords[MAXROOMSIZE];

public:
	GenerateMap();
	int GetEndLocation() { return endLoc[0]; }
	~GenerateMap();
};