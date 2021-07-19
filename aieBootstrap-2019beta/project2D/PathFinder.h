#pragma once
#include "GridNode.h"
#include "Heap.h"
#include "DynamicArray.h"
#include "Renderer2D.h"

#define NEIGHBOUR_COUNT 8
#define GRID_SIZE 104
#define NODE_SIZE 7
#define DIAGONAL_COST 14
#define STRAIGHT_COST 10


class PathFinder
{
public:
	// Constructor
	PathFinder();

	// Destructor
	~PathFinder();

	// Draws the grid
	void DrawGrid(aie::Renderer2D* renderer);

	// Draws the star node
	void DrawStart(aie::Renderer2D* renderer, GridNode* start);

	// Draws the end node
	void DrawEnd(aie::Renderer2D* renderer, GridNode* end);

	// Finds and draws the path 
	void PathFind(aie::Renderer2D* renderer, GridNode* start, GridNode* end, int pathfindtype);

	// Returns a neighbour node
	GridNode* GetNeighbour(int currentX, int currentY, int neighbour);

	// Returs a noby by its position
	GridNode* GetNodeByPos(int x, int y);

	// Dijkstras shortest path algorithm
	bool DijkstrasPath(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath, DynamicArray<GridNode*>& openListArray);

	// The heuristic for the A* algorithm
	int Heuristic(GridNode* current, GridNode* end);

	// A* algorithm for pathfinding
	bool AStar(int startX, int startY, int endX, int endY, DynamicArray<GridNode*>& finalPath, DynamicArray<GridNode*>& openListArray);

	// checks if the node is blocked off
	bool IsBlocked(int x, int y);

	// Blocks the Node
	void SetBlocked(int x, int y);
	
	// Unblocks the node
	void Unblock(int x, int y);
	
	DynamicArray<GridNode*> GetFinalPath();

private:

	// The grid
	GridNode* m_Grid[GRID_SIZE][GRID_SIZE];

	// A bool array holding the closedlis array
	bool m_InClosedList[GRID_SIZE][GRID_SIZE] = { 0 };

	// A bool array holding the openlists node
	bool m_InOpenList[GRID_SIZE][GRID_SIZE] = { 0 };

	// An array of closed list nodes
	DynamicArray<GridNode*> m_ClosedList;

	// An array of open list nodes
	DynamicArray<GridNode*> m_FinalPath;

	// A heap of nodes for an open list
	Heap* m_OpenList;
};

