#include "PathFinder.h"

// Creates the grid
PathFinder::PathFinder()
{
	// Creates an openlist
	m_OpenList = new Heap();

	// Loops initialising the grid's node
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			m_Grid[x][y] = new GridNode();
			m_Grid[x][y]->position.x = x;
			m_Grid[x][y]->position.y = y;
			m_Grid[x][y]->traversable = true;
			m_InOpenList[x][y] = false;
			m_InClosedList[x][y] = false;
		}
	} 
}

// Deletes the grid and all its elements
PathFinder::~PathFinder()
{
	// Loops deleting the grid's nodes
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			delete m_Grid[x][y];
			m_Grid[x][y] = nullptr;
		}
	}

	delete m_OpenList;
	m_OpenList = nullptr;
}

// Draws the starting point 
void PathFinder::DrawStart(aie::Renderer2D* renderer, GridNode* start)
{	
	//if the node is placed it will colour the node
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
	//if the node is placed it will colour the node
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

// Draws the grid using its nodes
void PathFinder::DrawGrid(aie::Renderer2D* renderer)
{
	//loops Drawing all thenodes
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			// if the grid node is blocked it will draw it blocked out
			if (!m_Grid[x][y]->traversable)
			{
				renderer->SetRenderColour(0, 0, 0, 255);
				renderer->DrawBox((m_Grid[x][y]->position.x * NODE_SIZE), (m_Grid[x][y]->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
			}

			else
			{
				renderer->SetRenderColour(255, 255, 255, 255);
				renderer->DrawBox((m_Grid[x][y]->position.x * NODE_SIZE), (m_Grid[x][y]->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
			}
		}
	}
}

// Choses a pathfinding mathod and pathfinds
void PathFinder::PathFind(aie::Renderer2D* renderer, GridNode* start, GridNode* end, int pathfindType)
{
	GridNode* node;
	
	// Pathfinding method changes depending on choise
	// Dijkstras
	if (pathfindType == 1)
	{
		if (DijkstrasPath(start->position.x, start->position.y, end->position.x, end->position.y, m_FinalPath, m_ClosedList))
		{
			renderer->SetRenderColour(0, 255, 100, 255);
			for (int i = 0; i < m_FinalPath.size(); i++)
			{
				GridNode* node;
				node = m_FinalPath[i];
				renderer->DrawBox((node->position.x * NODE_SIZE), (node->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
			}
		}
	}

	// A*
	else if (pathfindType == 2)
	{
		if (AStar(start->position.x, start->position.y, end->position.x, end->position.y, m_FinalPath, m_ClosedList))
		{
			renderer->SetRenderColour(0, 255, 100, 1.0f);
			for (int i = 0; i < m_FinalPath.size(); i++)
			{
				node = m_FinalPath[i];
				renderer->DrawBox((node->position.x * NODE_SIZE), (node->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
			}
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

	return m_Grid[x][y];
}

// Returns a node from its position
GridNode* PathFinder::GetNodeByPos(int x, int y)
{
	if (m_Grid[x][y] != nullptr)
	{
		return m_Grid[x][y];
	}

	else
	{
		return nullptr;
	}
}

// The Dijkstras shortest path algorithm
bool PathFinder::DijkstrasPath(int startX, int startY, int endX, int endY, std::vector<GridNode*>& finalPath, std::vector<GridNode*>& closedList)
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
	finalPath.clear();
	closedList.clear();

	 //Check for invalid path
	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (!end->traversable)
		return false;

	//Clear open list
	m_OpenList->Clear();
	memset(m_InOpenList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	// Clear closed list
	memset(m_InClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//Reset start nodes G score and pPrev
	start->score.f = 0;
	start->previous = nullptr;

	//Add start node to open list
	m_OpenList->Push(start);
	int f; 
	//While the open list is not empty
	while (m_OpenList->Size() > 0)
	{
		//Get cheapest node from open list and call it Current. 
		//Also remove it from the open list
		current = m_OpenList->Pop();
		m_InOpenList[current->position.x][current->position.y] = false;

		//Add Current to closed list
		m_InClosedList[current->position.x][current->position.y] = true;
		closedList.push_back(current);

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
				finalPath.push_back(current);
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
			if (neighbour == nullptr || !neighbour->traversable || m_InClosedList[neighbour->position.x][neighbour->position.y])
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
				if (m_InOpenList[neighbour->position.x][neighbour->position.y] == true)
				{
					//Check if the new path's G score is less than the neighbours G score
					//If so, update the neighbours G score and Prev
					if (f < neighbour->score.f)
					{
						neighbour->score.f = f;
						neighbour->previous = current;
					}
				}
				
				else
				{
				//Calculate the neighbours G score and Prev 
					neighbour->score.f = f;
					neighbour->previous = current;

					//Add neighbour to open list
					m_OpenList->Push(neighbour);
					m_InOpenList[neighbour->position.x][neighbour->position.y] = true;
				}
			}
		}
	}

	//Ran out of nodes and didn't find the path
	return false;
}

// The heuristic for A*
int PathFinder::Heuristic(GridNode* current, GridNode* end)
{
	int dx, dy;
	dx = abs(current->position.x - end->position.x);
	dy = abs(current->position.y - end->position.y);

	return STRAIGHT_COST * (dx + dy) + (DIAGONAL_COST - 2 * STRAIGHT_COST) * fmin(dx, dy);
}

// the A* pathfinding algorithm
bool PathFinder::AStar(int startX, int startY, int endX, int endY, std::vector<GridNode*>& finalPath, std::vector<GridNode*>& closedList)
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
	finalPath.clear();
	closedList.clear();

	//Check for invalid path
	if (start == nullptr)
		return false;
	if (end == nullptr)
		return false;
	if (!end->traversable)
		return false;


	//Clear open list
	m_OpenList->Clear();
	memset(m_InOpenList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	// Clear closed list
	memset(m_InClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	//Reset start nodes G score and pPrev
	start->score.g = 0;
	start->score.f = 0;
	start->score.h = 0;
	start->previous = nullptr;

	//Add start node to open list
	m_OpenList->Push(start);

	int g, f ,h;
	//While the open list is not empty
	while (m_OpenList->Size() > 0)
	{
		//Get cheapest node from open list and call it Current. 
		//Also remove it from the open list
		current = m_OpenList->Pop();
		m_InOpenList[current->position.x][current->position.y] = false;

		//Add Current to closed list
		m_InClosedList[current->position.x][current->position.y] = true;

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
				finalPath.push_back(current);
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
			if (neighbour == nullptr || !neighbour->traversable || m_InClosedList[neighbour->position.x][neighbour->position.y])
			{
				continue;
			}

			else
			{
				closedList.push_back(neighbour);
				g = current->score.g;
				if (n == 0 || n == 2 || n == 5 || n == 7)
				{
					g += 14;
				}

				else
				{
					g += 10;
				}

				h = Heuristic(neighbour, end);
				f = g + h;

				//Check if neighbour is in open list
				if (m_InOpenList[neighbour->position.x][neighbour->position.y] == true)
				{
					//Check if the new path's G score is less than the neighbours G score
					//If so, update the neighbours G score and Prev
					if (f < neighbour->score.f)
					{
						neighbour->score.g = g;
						neighbour->score.f = f;
						neighbour->previous = current;
					}
				}
				//else
				else
				{
					//Calculate the neighbours G score and Prev 
					neighbour->score.g = g;
					neighbour->score.f = f;
					neighbour->previous = current;

					//Add neighbour to open list
					m_OpenList->Push(neighbour);
					m_InOpenList[neighbour->position.x][neighbour->position.y] = true;
				}
			}
		}
	}

	//Ran out of nodes and didn't find the path
	return false;
}


// Returns if the node is blocked
bool PathFinder::IsBlocked(int x, int y)
{
	if (m_Grid[x][y]->traversable)
	{
		return true;
	}

	else
	{
		return false;
	}
}

// Blocks the node
void PathFinder::SetBlocked(int x, int y)
{
	GridNode* temp;
	temp = GetNodeByPos(x, y);
	temp->traversable = false;
}

// Unblocks the node
void PathFinder::Unblock(int x, int y)
{
	GridNode* temp;
	temp = GetNodeByPos(x, y);
	temp->traversable = true;
}

std::vector<GridNode*>& PathFinder::GetFinalPath()
{
	return m_FinalPath;
}
