// A-StarProject.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "MapLoading.h"
#include "aStarAlgo.h"
#include <deque>
using namespace tle;

void main()
{

	MapCreation MapStart("Maps\\Map");
	int map[mapSize][mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			map[i][j] = MapStart.GetMap(i, j);
		}
	}
	AstarAlogrithm Algo(MapStart.GetBeginningNode(),MapStart.GetEndNode());
	node* path = Algo.Algorithm(map);
	node* temp = path;
	int endX = path->x;
	int endY = path->y;
	int steps = path->stepsTaken;
	deque<int> pathX; deque<int> pathY;
	int tmpX; int tmpY;
	for (int i = 0; i < steps; i++)
	{
		tmpX = (temp->x * 10);
		tmpY = (temp->y * 10);
		temp = temp->parent;
		pathX.push_front(tmpX);
		pathY.push_front(tmpY);
	}
	int startX = temp->x;
	int startY = temp->y;
	tmpX = startX * 10; pathX.push_front(tmpX);
	tmpY = startY * 10; pathY.push_front(tmpY);
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media");
	ICamera* camera = myEngine->CreateCamera(kFPS,50,100,50);
	camera->RotateLocalX(90);

	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");
	IModel* cube[100];
	IMesh* playerMesh = myEngine->LoadMesh("Cube.x");
	IModel* player = playerMesh->CreateModel(pathX.front(), 10, pathY.front());
	pathX.pop_front(); pathY.pop_front();
	player->Scale(0.5f);
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cube[num] = cubeMesh->CreateModel(j * 10, 0, i * 10);
			if (map[i][j] == 0)
			{
				cube[num]->ScaleY(2.0f);
			}
			else if (startX == j && startY == i)
			{
				cube[num]->SetSkin("BaizeDark.jpg");
			}
			else if (endX == j && endY == i)
			{
				cube[num]->SetSkin("CueMetal.jpg");
			}
			else if (map[i][j] == 1)
			{
				cube[num]->SetSkin("stone2.jpg");
			}
			else if (map[i][j] == 2)
			{
				cube[num]->SetSkin("brick1.jpg");
			}
			else if (map[i][j] == 3)
			{
				cube[num]->SetSkin("Baize.jpg");
			}
			num++;
		}
	}

	/**** Set up your scene here ****/


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
			if (pathX.size() == 0 || pathY.size() == 0)
			{

			}
			else
			{
				player->SetX(pathX.front());
				player->SetZ(pathY.front());
				pathX.pop_front();
				pathY.pop_front();
			}
		}

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
