#include "PathFinder.h"

// Creates the grid
PathFinder::PathFinder()
{
	openList = new Heap();

	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			grid[x][y] = new GridNode();
			grid[x][y]->position.x = x;
			grid[x][y]->position.y = y;
			grid[x][y]->traversable = true;
			inOpenList[x][y] = false;
			inClosedList[x][y] = false;
		}
	} 
}

// Deletes the grid and all its elements
PathFinder::~PathFinder()
{
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			delete grid[x][y];
			grid[x][y] = nullptr;
		}
	}

	delete openList;
	openList = nullptr;
}

// Draws the starting point 
void PathFinder::DrawStart(aie::Renderer2D* renderer, GridNode* start)
{
	if (start->placed)
	{
		renderer->SetRenderColour(0, 255, 0, 255);
		renderer->DrawBox((start->position.x * NODE_SIZE), (start->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
	}
	else
	{
		renderer->SetRenderColour(255, 255, 255, 255);
		renderer->DrawBox((start->position.x * NODE_SIZE), (start->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
	}
}

// Draws the ending point
void PathFinder::DrawEnd(aie::Renderer2D* renderer, GridNode* end)
{
	if (end->placed)
	{
		renderer->SetRenderColour(255, 0, 0, 255);
		renderer->DrawBox((end->position.x * NODE_SIZE), (end->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE *0.9f, 0.0f, 0.0f);
	}
	else
	{
		renderer->SetRenderColour(255, 255, 255, 255);
		renderer->DrawBox((end->position.x * NODE_SIZE), (end->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
	}
}

// Draws the grid
void PathFinder::DrawGrid(aie::Renderer2D* renderer)
{
	

	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			if (!grid[x][y]->traversable)
			{
				renderer->SetRenderColour(0, 0, 0, 255);
				renderer->DrawBox((grid[x][y]->position.x * NODE_SIZE), (grid[x][y]->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
			}

			else
			{
				renderer->SetRenderColour(255, 255, 255, 255);
				renderer->DrawBox((grid[x][y]->position.x * NODE_SIZE), (grid[x][y]->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
			}
		}
	}
}

void PathFinder::PathFind(aie::Renderer2D* renderer, GridNode* start, GridNode* end)
{
	if (DijkstrasPath(start->position.x, start->position.y, end->position.x, end->position.y, finalPath))
	{
		renderer->SetRenderColour(0, 0, 255, 255);
		for (int i = 0; i < finalPath.GetSize(); i++)
		{
			GridNode* node;
			node = finalPath[i];
			renderer->DrawBox((node->position.x * NODE_SIZE), (node->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
		}
	}
}

// Returns The neighbours node
GridNode* PathFinder::GetNeighbour(int currentX, int currentY, int neighbour)
{
	int x = currentX;
	int y = currentY;

	switch (neighbour)
	{
	case 0: --x; ++y; break;
	case 1:      ++y; break;
	case 2: ++x; ++y; break;
	case 3: --x;      break;
	case 4: ++x;      break;
	case 5: --x; --y; break;
	case 6:      --y; break;
	case 7: ++x; --y; break;
	}

	if (x < 0 || x >= GRID_SIZE)
		return nullptr;

	if (y < 0 || y >= GRID_SIZE)
		return nullptr;

	return grid[x][y];
}

GridNode* PathFinder::GetNodeByPos(int x, int y)
{
	if (grid[x][y] != nullptr)
	{
		return grid[x][y];
	}

	else
	{
		return nullptr;
	}
}

bool PathFinder::DijkstrasPath(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath)
{
	GridNode* start;
	GridNode* end;
	GridNode* current;
	GridNode* neighbour;
	GridNode* temp;

	//Find start and end nodes GetNodeByPos
	start = GetNodeByPos(startX, startY);
	end = GetNodeByPos(endX, endY);

	 //Clear finalPath
	finalPath.Clear();

	 //Check for invalid path
	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (!end->traversable)
		return false;

	//Clear open list
	openList->Clear();
	memset(inOpenList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	// Clear closed list
	memset(inClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//Reset start nodes G score and pPrev
	start->score.f = 0;
	start->previous = nullptr;

	//Add start node to open list
	openList->Push(start);

	int f; 
	//While the open list is not empty
	while (openList->Size() > 0)
	{
		//Get cheapest node from open list and call it Current. 
		//Also remove it from the open list
		current = openList->Pop();
		inOpenList[current->position.x][current->position.y] = false;

		//Add Current to closed list
		inClosedList[current->position.x][current->position.y] = true;

		//If Current is equal to the end node then path has been found
		if (current == end)
		{
			//Starting at the end node, loop back through all pPrev nodes and add them
			//to final path
			if (current->previous != nullptr)
			{
				current = current->previous;
			}
			while(current->previous != nullptr)
			{				
				finalPath.Add(current);
				current = current->previous;
			}

			//We found the path
			return true;
		}

		//Loop through all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			//Get neighbour
			neighbour = GetNeighbour(current->position.x, current->position.y, n);

			//Skip neighbour if it's null
			//Skip neighbour if it's blocked
			//Skip neighbour if it's in the closed list
			if (neighbour == nullptr || !neighbour->traversable || inClosedList[neighbour->position.x][neighbour->position.y])
			{
				continue;
			}

			else
			{ 
				f = current->score.f; 
				if (n == 0 || n == 2 || n == 5 || n == 7)
				{
					f += 14;
				}

				else
				{
					f += 10;
				}
				//Check if neighbour is in open list
				if (inOpenList[neighbour->position.x][neighbour->position.y] == true)
				{
					//Check if the new path's G score is less than the neighbours G score
					//If so, update the neighbours G score and Prev
					if (f < neighbour->score.f)
					{
						neighbour->score.f = f;
						neighbour->previous = current;
					}
				}
				//else
				else
				{
				//Calculate the neighbours G score and Prev 
					neighbour->score.f = f;
					neighbour->previous = current;

					//Add neighbour to open list
					openList->Push(neighbour);
					inOpenList[neighbour->position.x][neighbour->position.y] = true;

				}

			}
		}
	}

	//Ran out of nodes and didn't find the path
	return false;
}



bool PathFinder::ScuffedDijkstrasPath(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath)
{
	GridNode* start;
	GridNode* end;
	GridNode* current;
	GridNode* neighbour;
	GridNode* temp;

	//Find start and end nodes GetNodeByPos
	start = GetNodeByPos(startX, startY);
	end = GetNodeByPos(endX, endY);

	//Clear finalPath
	finalPath.Clear();

	//Check for invalid path
	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (!end->traversable)
		return false;

	//Clear open list
	openList->Clear();
	memset(inOpenList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	// Clear closed list
	memset(inClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//Reset start nodes G score and pPrev
	start->score.g = 0;
	start->previous = nullptr;

	//Add start node to open list
	openList->Push(start);

	int g;
	//While the open list is not empty
	while (openList->Size() > 0)
	{
		//Get cheapest node from open list and call it Current. 
		//Also remove it from the open list
		current = openList->Pop();
		inOpenList[current->position.x][current->position.y] = false;

		//Add Current to closed list
		inClosedList[current->position.x][current->position.y] = true;

		//If Current is equal to the end node then path has been found
		if (current == end)
		{
			//Starting at the end node, loop back through all pPrev nodes and add them
			//to final path
			if (current->previous != nullptr)
			{
				current = current->previous;
			}
			while (current->previous != nullptr)
			{
				finalPath.Add(current);
				current = current->previous;
			}

			//We found the path
			return true;
		}

		//Loop through all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			//Get neighbour
			neighbour = GetNeighbour(current->position.x, current->position.y, n);

			//Skip neighbour if it's null
			//Skip neighbour if it's blocked
			//Skip neighbour if it's in the closed list
			if (neighbour == nullptr || !neighbour->traversable || inClosedList[neighbour->position.x][neighbour->position.y])
			{
				continue;
			}

			else
			{
				g = current->score.g;
				if (n == 0 || n == 2 || n == 5 || n == 7)
				{
					g += 14;
				}

				else
				{
					g += 10;
				}
				//Check if neighbour is in open list
				if (inOpenList[neighbour->position.x][neighbour->position.y] == true)
				{
					//Check if the new path's G score is less than the neighbours G score
					//If so, update the neighbours G score and Prev
					if (g < neighbour->score.g)
					{
						neighbour->score.g = g;
						neighbour->previous = current;
					}
				}
				//else
				else
				{
					//Calculate the neighbours G score and Prev 
					neighbour->score.g = g;
					neighbour->previous = current;

					//Add neighbour to open list
					openList->Push(neighbour);
					inOpenList[neighbour->position.x][neighbour->position.y] = true;

				}

			}
		}
	}

	//Ran out of nodes and didn't find the path
	return false;
}


bool PathFinder::AStar(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath)
{
	GridNode* start;
	GridNode* end;
	GridNode* current;
	GridNode* neighbour;
	GridNode* temp;

	//Find start and end nodes GetNodeByPos
	start = GetNodeByPos(startX, startY);
	end = GetNodeByPos(endX, endY);

	//Clear finalPath
	finalPath.Clear();

	//Check for invalid path
	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (!end->traversable)
		return false;


	//Clear open list
	openList->Clear();
	memset(inOpenList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	// Clear closed list
	memset(inClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//Reset start nodes G score and pPrev
	start->score.g = 0;
	start->previous = nullptr;

	//Add start node to open list
	openList->Push(start);

	int g;
	//While the open list is not empty
	while (openList->Size() > 0)
	{
		//Get cheapest node from open list and call it Current. 
		//Also remove it from the open list
		current = openList->Pop();
		inOpenList[current->position.x][current->position.y] = false;

		//Add Current to closed list
		inClosedList[current->position.x][current->position.y] = true;

		//If Current is equal to the end node then path has been found
		if (current == end)
		{
			//Starting at the end node, loop back through all pPrev nodes and add them
			//to final path
			if (current->previous != nullptr)
			{
				current = current->previous;
			}
			while (current->previous != nullptr)
			{
				finalPath.Add(current);
				current = current->previous;
			}

			//We found the path
			return true;
		}

		//Loop through all neighbours
		for (int n = 0; n < NEIGHBOUR_COUNT; ++n)
		{
			//Get neighbour
			neighbour = GetNeighbour(current->position.x, current->position.y, n);

			//Skip neighbour if it's null
			//Skip neighbour if it's blocked
			//Skip neighbour if it's in the closed list
			if (neighbour == nullptr || !neighbour->traversable || inClosedList[neighbour->position.x][neighbour->position.y])
			{
				continue;
			}

			else
			{
				g = current->score.g;
				if (n == 0 || n == 2 || n == 5 || n == 7)
				{
					g += 14;
				}

				else
				{
					g += 10;
				}
				//Check if neighbour is in open list
				if (inOpenList[neighbour->position.x][neighbour->position.y] == true)
				{
					//Check if the new path's G score is less than the neighbours G score
					//If so, update the neighbours G score and Prev
					if (g < neighbour->score.g)
					{
						
						neighbour->score.g = g;
						neighbour->previous = current;
					}
				}
				//else
				else
				{
					//Calculate the neighbours G score and Prev 
					neighbour->score.g = g;
					neighbour->previous = current;

					//Add neighbour to open list
					openList->Push(neighbour);
					inOpenList[neighbour->position.x][neighbour->position.y] = true;

				}

			}
		}
	}

	//Ran out of nodes and didn't find the path
	return false;
}


void PathFinder::SetBlocked(int x, int y)
{
	GridNode* temp;
	temp = GetNodeByPos(x, y);
	temp->traversable = false;
}