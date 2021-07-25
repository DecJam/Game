#pragma once
#include "Vector2.h"
#include "GridNode.h"
#include "PathFinder.h"
#include "DynamicArray.h"
#include "Renderer2D.h"

class Agent
{
public:

	Agent();
	~Agent();

	void Update(aie::Renderer2D* renderer, aie::Font* font, PathFinder* pathfinder);
	void Draw(aie::Renderer2D* renderer, aie::Font* font, PathFinder* pathfinder);
	
private:


	GridNode* m_Position;
	GridNode* m_Destination;

	DynamicArray<GridNode*> m_FinalList;

};

