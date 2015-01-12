#include "MapLoading.h"

MapCreation::MapCreation(std::string mapInput)
{
	std::string mapName = mapInput + ".txt";
	std::string mapData = mapInput + "BE.txt";

	std::ifstream inp;
	std::ofstream ofp;

	inp.open(mapData);
	inp >> beginningNode[0];
	inp >> beginningNode[1];
	inp >> endNode[0];
	inp >> endNode[1];

	inp.close();
	inp.open(mapName);

	int num = 0;
	char temp[mapSize+1][mapSize];
	while (!inp.eof())
	{
		inp >> temp[num];
		num++;
	}
	inp.close();

	for (int i = 0; i<mapSize; i++)
	{
		for (int j = 0; j<mapSize; j++)
		{
			map[i][j] = temp[i][j] - 48;
		}
	}
}