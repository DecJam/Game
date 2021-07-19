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

	void Update(aie::Renderer2D* renderer, aie::Font* font);
	void Draw(aie::Renderer2D* renderer, aie::Font* font);
	
private:
	

	PathFinder* m_Pathfinder;

	Vector2* m_Position;
	Vector2* m_Destination;

	GridNode* m_Start;
	GridNode* m_End;

	DynamicArray<GridNode*> FinalList;

};

