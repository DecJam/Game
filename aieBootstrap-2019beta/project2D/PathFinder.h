#pragma once
#include "GridNode.h"
#include "Heap.h"
#include "DynamicArray.h"
#include "Renderer2D.h"

#define NEIGHBOUR_COUNT 8
#define GRID_SIZE 100
#define NODE_SIZE 8

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	void DrawGrid(aie::Renderer2D* renderer);
	void DrawStart(aie::Renderer2D* renderer, GridNode* start);
	void DrawEnd(aie::Renderer2D* renderer, GridNode* end);
	void DrawBlocked(aie::Renderer2D* renderer);
	void PathFind(aie::Renderer2D* renderer, GridNode* start, GridNode* end);
	GridNode* GetNeighbour(int currentX, int currentY, int neighbour);
	GridNode* GetNodeByPos(int x, int y);
	bool DijkstrasPath(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath);
	bool ScuffedDijkstrasPath(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath);

	bool AStar(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath);

	void SetBlocked(int x, int y);


private:

	GridNode* grid[GRID_SIZE][GRID_SIZE];
	bool inClosedList[GRID_SIZE][GRID_SIZE] = { 0 };
	bool inOpenList[GRID_SIZE][GRID_SIZE] = { 0 };
	DynamicArray<GridNode*> finalPath;
	Heap* openList;
};

