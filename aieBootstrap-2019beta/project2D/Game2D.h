#pragma once

#include "Game.h"
#include "GridNode.h"
#include "Renderer2D.h"
#include "PathFinder.h"
#include "DynamicArray.h"
#include "Agent.h"

class Game2D : public aie::Game
{
public:

	// Loads game
	Game2D(const char* title, int width, int height, bool fullscreen);

	// Game's destructor
	virtual ~Game2D();

	// Games update loop
	virtual void Update(float deltaTime);

	// Game's drawing
	virtual void Draw();

	void TogglePathfindType();

protected:

	// Renderer
	aie::Renderer2D* m_2DRenderer;

	// Font
	aie::Font* m_Font;
	
	// Pathfinder
	PathFinder* m_Pathfinder;

	// Starting node
	GridNode* m_Start;

	// Ending node
	GridNode* m_End;
	
	// An agent
	Agent* m_Agent;

	// Type of pathfinding used
	int m_PathfindType;

	// Timer for delays
	float m_Timer;
};