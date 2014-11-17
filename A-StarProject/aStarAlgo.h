#include <math.h>

const int mapSize2 = 10;


struct node
{
	int x;
	int y;
	int cost;
	int score;
	int stepsTaken;
	node* parent;
};

class AstarAlogrithm
{
private:
	int startLoc[2];
	int endLoc[2];
	node* start;
	node* end;
	node* current;
	node* tmp;
	int nodeNumX[4];
	int nodeNumY[4];
public:
	AstarAlogrithm(int start[2], int end[2]);
	node* Algorithm(int map[][mapSize2]);
	node* NodeGeneration(int number, int x, int y, int map[][mapSize2]);
	int ManhattanDistance(int X, int Y, int endX, int endY) // Heuristic being used
	{ int manhattanDistance = 0; manhattanDistance = abs(X - endX) + abs(Y - endY); return manhattanDistance;}
};