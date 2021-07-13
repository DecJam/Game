#pragma once

struct GridNode
{
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
	
	bool placed;
	Position position;
	Scores score;
	int traversalCost;
	GridNode* previous;
	bool traversable;
};

