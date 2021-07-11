#pragma once
#include "GridNode.h"
#include "Heap.h"
#include "DynamicArray.h"
#include "Renderer2D.h"

#define NEIGHBOUR_COUNT 8
#define GRID_HEIGHT 50
#define GRID_WIDTH 50
#define NODE_SIZE 10

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	void Draw(aie::Renderer2D* renderer);
	void PathFind(aie::Renderer2D* renderer);


	GridNode* grid[GRID_HEIGHT][GRID_WIDTH];

private:

	Heap closedList;
	Heap openList;
};

