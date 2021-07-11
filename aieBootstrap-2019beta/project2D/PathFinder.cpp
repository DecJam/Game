#include "PathFinder.h"

PathFinder::PathFinder()
{
	for (int x = 0; x < GRID_HEIGHT; x++)
	{
		for (int y = 0; y < GRID_WIDTH; y++)
		{
			grid[x][y] = new GridNode();
			grid[x][y]->position.x = x;
			grid[x][y]->position.y = y;
			grid[x][y]->lit = false;
		}
	} 
	
	for (int x = 0; x < GRID_HEIGHT; x++)
	{
		for (int y = 0; y < GRID_WIDTH; y++)
		{
		
			/*
			Reference neighbours
				0 | 1 | 2
				3 | x | 4
				5 | 6 | 7
			*/

			for (int i = 0; i < NEIGHBOUR_COUNT; i++)
			{
				struct Vector2
			{
				int x;
				int y;
			};
				Vector2 neighbourPos;
				neighbourPos.x = grid[x][y]->position.x;
				neighbourPos.y = grid[x][y]->position.y;

				switch (i)
				{
				case 0: {--neighbourPos.x;	++neighbourPos.y;} break;
				case 1: {					++neighbourPos.y;} break;
				case 2: {++neighbourPos.x;	++neighbourPos.y;} break;
				case 3: {--neighbourPos.x;					 } break;
				case 4: {++neighbourPos.x;					 } break;
				case 5: {--neighbourPos.x;	--neighbourPos.y;} break;
				case 6: {					--neighbourPos.y;} break;
				case 7: {++neighbourPos.x;	--neighbourPos.y;} break;
				}

				if (neighbourPos.x >= 0 && neighbourPos.x < GRID_WIDTH && neighbourPos.y >= 0 && neighbourPos.y < GRID_HEIGHT)
				{
					grid[x][y]->neighbours[i].node = grid[neighbourPos.x][neighbourPos.y];

				}

				else
				{
					grid[x][y]->neighbours[i].node = nullptr;
				}
			}
		}
	}
}


PathFinder::~PathFinder()
{
	
}

void PathFinder::Draw(aie::Renderer2D* renderer)
{
	for (int x = 0; x < GRID_HEIGHT; x++)
	{
		for (int y = 0; y < GRID_WIDTH; y++)
		{
			renderer->DrawBox((x * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE)), ( y * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE)), NODE_SIZE, NODE_SIZE, 0.0f, 0.0f);
		}
	}
	int x = 15;
	int y = 15;
	
	DynamicArray<GridNode*> neighbours;
	GridNode* node;
	node = grid[x][y];

	for (int l = 0; l < neighbours.GetSize(); l++)
	{
		node = neighbours[l];

		for (int v = 0; v < NEIGHBOUR_COUNT; v++)
		{
			if (node->neighbours[v].node->lit == false)
			{
				neighbours.Add(node->neighbours[v].node);
			}
		}

	}

	for (int i = 0; i < neighbours.GetSize(); i++)
	{
		renderer->DrawBox(neighbours[i]->position.x * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE), neighbours[i]->position.y * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE), NODE_SIZE, NODE_SIZE, 0.0f, 0.0f);
	}
//	neighbours.Add(*grid[x][y]->neighbours[l]);
	

	//renderer->SetRenderColour(100, 0, 0, 100);
	//renderer->DrawBox((grid[x][y]->position.x * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE)), (grid[x][y]->position.y * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE)), NODE_SIZE, NODE_SIZE, 0.0f, 0.0f);
	//

	//renderer->SetRenderColour(0, 100, 0 , 100);
	//for (int i = 0; i < NEIGHBOUR_COUNT; i++)
	//{
	//	if (grid[x][y]->neighbours[i].node->lit != true, grid[x][y]->neighbours[i].node != nullptr)
	//	{
	//		renderer->DrawBox((grid[x][y]->neighbours[i].node->position.x * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE)), (grid[x][y]->neighbours[i].node->position.y * (1.5 * NODE_SIZE) + (0.5 * NODE_SIZE)), NODE_SIZE, NODE_SIZE, 0.0f, 0.0f);
	//		grid[x][y]->lit = true;
	//	}
	//}

	
	// draw specified grid and its neighbours
}

void PathFinder::PathFind(aie::Renderer2D* renderer)
{

}


