#pragma once
#include "Vector2.h"

struct GridNode
{

	// Scores for pathfinding
	struct Scores
	{
		int f;
		int h;
		int g;
	};
	
	// If the node has been placed
	bool placed;

	// The nodes position 
	Vector2 position;

	// The nodes scores
	Scores score;

	// The Nodes previos node
	GridNode* previous;

	// Is the node able to be crossed?
	bool traversable;

};

