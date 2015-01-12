#include "aStarAlgo.h"
#include <iostream>
#include <deque>
#include <algorithm>


bool decompare(node* num1, node* num2) //Function used in sorting of open list
{
	return (num1->score < num2->score);
}

AstarAlogrithm::AstarAlogrithm(int start[2], int end[2])
{
	startLoc[0] = start[0]; startLoc[1] = start[1];
	endLoc[0] = end[0]; endLoc[1] = end[1];
}
node* AstarAlogrithm::Algorithm(int map[][mapSize2])
{
	current = new(node);
	tmp = new(node);
	bool found = false;
	nodeNumX[0] = 1;
	nodeNumX[1] = -1;
	nodeNumX[2] = 0;
	nodeNumX[3] = 0;
	nodeNumY[0] = 0;
	nodeNumY[1] = 0;
	nodeNumY[2] = 1;
	nodeNumY[3] = -1;

	start = new(node); end = new(node);

	end->x = endLoc[0]; end->y = endLoc[1]; end->cost = map[end->y][end->x]; end->stepsTaken = 0;
	end->score = end->cost + ManhattanDistance(end->x, end->y, end->x, end->y); end->parent = NULL;

	start->x = startLoc[0]; start->y = startLoc[1]; start->cost = 0; start->stepsTaken = 0;
	start->score = start->cost + ManhattanDistance(start->x, start->y, end->x, end->y); start->parent = NULL;

	std::deque <node*> openList;
	std::deque <node*> closedList;

	openList.push_back(start);

	while (found == false)
	{
		std::sort(openList.begin(), openList.end(), decompare);
		current = openList.front();
		openList.pop_front();
		if (current->x == end->x && current->y == end->y)
		{
			std::cout << "Found!" << std::endl;
			break;
		}
		else
		{
			closedList.push_back(current);
			for (int i = 0; i < 4; i++) // Code to generate each node is run 4 times, one for north south east and west of the current node
			{
				tmp = NodeGeneration(current->cost, (current->x + nodeNumX[i]), (current->y + nodeNumY[i]), map);
				bool open = false;
				bool closed = false;
				for (int i = 0; i < openList.size(); i++)
				{
					if (tmp->x == openList.at(i)->x && tmp->y == openList.at(i)->y && tmp->cost < openList.at(i)->cost)
					{

						openList.at(i)->cost = tmp->cost; // if found on the open list and has a lower score it will update what is currently on the open list
						openList.at(i)->parent = tmp->parent;
						open = true;
					}
					else if (tmp->x == openList.at(i)->x && tmp->y == openList.at(i)->y && tmp->cost >= openList.at(i)->cost)
					{
						open = true;
					}
				}
				for (int i = 0; i < closedList.size(); i++)
				{
					if (tmp->x == closedList.at(i)->x && tmp->y == closedList.at(i)->y && tmp->cost < closedList.at(i)->cost)
					{
						closedList.at(i)->cost = tmp->cost; // if the currently generated node is found on the closed list and its cost is smaller it updates the closed list node
						closedList.at(i)->parent = tmp->parent;
						openList.push_back(closedList.at(i));
						closed = true;
					}
					else if (tmp->x == closedList.at(i)->x && tmp->y == closedList.at(i)->y && tmp->cost >= closedList.at(i)->cost)
					{
						closed = true;
					}
				}
				if (tmp->cost > 1000)
				{
					//if the score is too high the node is discarded
				}
				else if (open == false && closed == false)
				{
					openList.push_back(tmp); // once a node is generated it is sent to the openlist
				}

			}
			if (openList.empty() == true)
			{
				std::cout << "Failed";
				break;
			}
		}
	}
	openList.clear();
	closedList.clear();
	return current;
}
node* AstarAlogrithm::NodeGeneration(int cost, int x, int y, int map[][mapSize2])
{
				node* tmp = new (node);
				tmp->cost = map[y][x];
				tmp->x = x;
				tmp->y = y;
				tmp->parent = current;
				if (tmp->cost <= 0 || tmp->cost > 1000)
				{
					tmp->cost = 10000;
				}
				else if (tmp->cost == 1)
				{
					tmp->cost = 1;
				}
				else if (tmp->cost == 2)
				{
					tmp->cost = 2;
				}
				else if (tmp->cost == 3)
				{
					tmp->cost = 3;
				}
				else if (tmp->cost == 4)
				{
					tmp->cost = 1;
				}
				tmp->stepsTaken = tmp->parent->stepsTaken + 1;
				tmp->score = (tmp->cost + ManhattanDistance(x, y, end->x, end->y)) + tmp->parent->score;
				return tmp;
}