#pragma once
#define MAX_NEIGHBOURS 8

struct GridNode
{
	struct Edge
	{
		GridNode* node;
	};

	struct Position
	{
		int x;
		int y;
	};

	struct Scores
	{
		int f;
		int h;
		int g;
	};
		
	bool lit;
	Position position;
	Scores score;
	int traversalCost;
	GridNode* previous;
	Edge neighbours[MAX_NEIGHBOURS];
};

