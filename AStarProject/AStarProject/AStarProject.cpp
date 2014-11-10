// AStarProject.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "MapGeneration.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Start";
	GenerateMap mapStart;
	int test = mapStart.GetEndLocation();
	std::cout << "Done";
	system("pause");

	return 0;
}

