// A-StarProject.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "MapLoading.h"
#include "aStarAlgo.h"
#include <deque>
using namespace tle;

struct mapModels
{
	IModel* cubes[100];
};

struct maps
{
	int mapType;
	int map[mapSize][mapSize];
	int startX;
	int startY;
	int endX;
	int endY;
	int steps;
	node* path;
	deque<int> pathX; 
	deque<int> pathY;
};

maps MapStorage(string mapName, int type)
{
	maps tmp;
	tmp.mapType = type;
	MapCreation MapStart(mapName, type);
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			tmp.map[i][j] = MapStart.GetMap(i, j);
		}
	}
	AstarAlogrithm Algo(MapStart.GetBeginningNode(), MapStart.GetEndNode());
	tmp.path = Algo.Algorithm(tmp.map);
	node* temp = tmp.path;
	tmp.endX = tmp.path->x;
	tmp.endY = tmp.path->y;
	tmp.steps = tmp.path->stepsTaken;
	int tmpX; int tmpY;
	for (int i = 0; i < tmp.steps; i++)
	{
		tmpX = (temp->x * 10);
		tmpY = (temp->y * 10);
		temp = temp->parent;
		tmp.pathX.push_front(tmpX);
		tmp.pathY.push_front(tmpY);
	}
	tmp.startX = temp->x;
	tmp.startY = temp->y;
	tmpX = tmp.startX * 10; tmp.pathX.push_front(tmpX);
	tmpY = tmp.startY * 10; tmp.pathY.push_front(tmpY);
	return tmp;
}
void MapSpawning(IMesh* cubeMesh, int map[mapSize][mapSize], int startX, int startY, int endX, int endY, int cubeX, int cubeY)
{
	mapModels cube;
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cube.cubes[num] = cubeMesh->CreateModel(cubeX + (j * 10), 0, cubeY + (i * 10));
			if (map[i][j] == 0)
			{
				cube.cubes[num]->ScaleY(2.0f);
			}
			else if (startX == j && startY == i)
			{
				cube.cubes[num]->SetSkin("BaizeDark.jpg");
			}
			else if (endX == j && endY == i)
			{
				cube.cubes[num]->SetSkin("CueMetal.jpg");
			}
			else if (map[i][j] == 1)
			{
				cube.cubes[num]->SetSkin("stone2.jpg");
			}
			else if (map[i][j] == 2)
			{
				cube.cubes[num]->SetSkin("brick1.jpg");
			}
			else if (map[i][j] == 3)
			{
				cube.cubes[num]->SetSkin("Baize.jpg");
			}
			num++;
		}
	}
}

void main()
{
	
	deque <maps> mapCollection;
	deque <int> fullMapX;
	deque <int> fullMapY;
	mapCollection.push_back(MapStorage("Maps\\FullMap", 0));
	fullMapX = mapCollection.at(0).pathX;
	fullMapY = mapCollection.at(0).pathY;
	mapCollection.push_back(MapStorage("Maps\\Complexity1\\1", 1));
	mapCollection.push_back(MapStorage("Maps\\StartEndRooms\\Start", 2));
	mapCollection.push_back(MapStorage("Maps\\StartEndRooms\\End", 3));
	int firstMap[mapSize][mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			firstMap[i][j] = mapCollection.at(0).map[i][j];
		}
	}

	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();


	// Camera Setup
	ICamera* camera = myEngine->CreateCamera(kFPS, 10, 100, 10);

	// Mesh Creation
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media");
	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");
	IMesh* playerMesh = myEngine->LoadMesh("Cube.x");

	
	// Model setup/creation
	int startX = 0;
	int startY = 0;
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			if (firstMap[i][j] == 5)
			{
				MapSpawning(cubeMesh, mapCollection.at(3).map, mapCollection.at(3).startX,
					mapCollection.at(3).startY, mapCollection.at(3).endX, mapCollection.at(3).endY, startX, startY);
			}
			if (firstMap[i][j] == 4)
			{
				MapSpawning(cubeMesh, mapCollection.at(2).map, mapCollection.at(2).startX,
					mapCollection.at(2).startY, mapCollection.at(2).endX, mapCollection.at(2).endY, startX, startY);
			}
			if (firstMap[i][j] == 1)
			{
				MapSpawning(cubeMesh, mapCollection.at(1).map, mapCollection.at(1).startX,
					mapCollection.at(1).startY, mapCollection.at(1).endX, mapCollection.at(1).endY, startX, startY);
			}
			if (firstMap[i][j] == 0)
			{

			}
			startX += 100;
		}
		startX = 0;
		startY += 100;
	} 

	IModel* player = playerMesh->CreateModel(mapCollection.at(2).pathX.front(), 10, mapCollection.at(2).pathY.front());
	mapCollection.at(2).pathX.pop_front(); mapCollection.at(2).pathY.pop_front();

	// Pre-set movement, any special settings before drawscene goes here
	camera->RotateLocalX(90);
	camera->AttachToParent(player);
	player->Scale(0.5f);

	// Any misc settings before drawing the scene
	deque<int> currentPathX;
	deque<int> currentPathY;

	currentPathX = mapCollection.at(2).pathX; currentPathY = mapCollection.at(2).pathY;
	currentPathX.pop_front(); currentPathY.pop_front(); // pop the front of the path X and Y

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
		if (myEngine->KeyHit(Key_Space))
		{
			if (currentPathX.size() == 0 && currentPathY.size() == 0)
			{
				int start[2];
				int end[2];
				if (fullMapX.at(1) > fullMapX.at(0))
				{
					start[0] = 0;
					start[1] = 4;
					end[2];
					if (fullMapX.at(2) > fullMapX.at(1))
					{
						end[0] = 9;
						end[1] = 4;
					}
					else if (fullMapY.at(2) > fullMapY.at(1))
					{
						end[0] = 4; 
						end[1] = 9;
					}

				}
				else if (fullMapY.at(1) > fullMapY.at(0))
				{
					start[0] = 4;
					start[1] = 0;
					int end[2];
					if (fullMapX.at(2) > fullMapX.at(1))
					{
						end[0] = 9; 
						end[1] = 4;
					}
					else if (fullMapY.at(2) > fullMapY.at(1))
					{
						end[0] = 4; 
						end[1] = 9;
					}
				}

				AstarAlogrithm NextBlockAStar(start, end);
				node* tmp = NextBlockAStar.Algorithm(mapCollection.at(1).map);
				int tmpX;
				int tmpY;
				int steps = tmp->stepsTaken;
				for (int i = 0; i < steps; i++)
				{
					tmpX = (tmp->x * 10);
					tmpY = (tmp->y * 10);
					tmp = tmp->parent;
					currentPathX.push_front(tmpX);
					currentPathY.push_front(tmpY);
				}
			}
			else
			{
				player->SetX(currentPathX.front());
				player->SetZ(currentPathY.front());
				currentPathX.pop_front();
				currentPathY.pop_front();
			}
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
