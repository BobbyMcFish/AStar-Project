#include "stdafx.h"
#include "MapGeneration.h"


GenerateMap::GenerateMap()
{
	inp.open("Map.txt");
	int num = 0;
	while (!inp.eof());
	{
		inp >> yCoords[num].xCoordsChar;
		num++;
	}
	inp.close();
	inp.open("BeginningEndNodes.txt");
	inp >> startLoc[0];
	inp >> startLoc[1];
	inp >> endLoc[0];
	inp >> endLoc[1];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			yCoords[i].xCoords[j] = yCoords[i].xCoordsChar[j];
			yCoords[i].xCoords[j] = yCoords[i].xCoords[j] - 48;
		}
	}
	cout << "Done!";
}
GenerateMap::~GenerateMap()
{

}