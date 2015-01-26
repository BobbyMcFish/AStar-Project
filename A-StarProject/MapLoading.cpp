#include "MapLoading.h"

MapCreation::MapCreation(std::string mapInput, int num)
{
	std::string mapName = mapInput + ".txt";
	std::ifstream inp;
	std::ofstream ofp;
	
	if (num == 4 || num == 0 || num == 5)
	{
		std::string mapData = mapInput + "BE.txt";
		inp.open(mapData);
		inp >> beginningNode[0];
		inp >> beginningNode[1];
		inp >> endNode[0];
		inp >> endNode[1];
		inp.close();
	}
	else
	{
		beginningNode[0] = 0;
		beginningNode[1] = 0;
		endNode[0] = 9;
		endNode[1] = 9; 
	}

	inp.open(mapName);

	int tmpnum = 0;
	char temp[mapSize+1][mapSize];
	while (!inp.eof())
	{
		inp >> temp[tmpnum];
		tmpnum++;
	}
	inp.close();

	for (int i = 0; i<tmpnum; i++)
	{
		for (int j = 0; j<mapSize; j++)
		{
			map[i][j] = temp[i][j] - 48;
		}
	}
}