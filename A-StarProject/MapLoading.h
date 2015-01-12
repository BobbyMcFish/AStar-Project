#include <fstream>
#include <iostream>
#include <string>

const int mapSize = 10;

class MapCreation{
private:
	int beginningNode[2];
	int endNode[2];
	int map[mapSize][mapSize];
public:
	MapCreation(std::string map);
	int GetMap(int i, int j) { return map[i][j]; }
	int* GetBeginningNode() { return beginningNode; }
	int* GetEndNode() { return endNode; }
};