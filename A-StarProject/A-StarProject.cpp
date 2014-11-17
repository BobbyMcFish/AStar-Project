// A-StarProject.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "MapLoading.h"
#include "aStarAlgo.h"
using namespace tle;

void main()
{

	MapCreation MapStart("Map");
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
	int endX = path->x;
	int endY = path->y;
	int steps = path->stepsTaken;
	for ()

	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	ICamera* camera = myEngine->CreateCamera(kFPS);

	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");
	IModel* cube[100];
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

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
