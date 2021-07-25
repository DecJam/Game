#include "Agent.h"

Agent::Agent()
{
	m_Position = new GridNode();
	m_Destination = new GridNode();
	m_Position->position.x = 10;
	m_Position->position.y = 10;
	m_Destination->position.x = 100;
	m_Destination->position.y = 100;
	m_Position->placed = true;
	m_Destination->placed = true;
}

Agent::~Agent()
{
}

void Agent::Update(aie::Renderer2D* renderer, aie::Font* font, PathFinder* pathfinder)
{
	pathfinder->PathFind(renderer, m_Position, m_Destination, 2);
	m_FinalList = pathfinder->GetFinalPath();
}

void Agent::Draw(aie::Renderer2D* renderer, aie::Font* font, PathFinder* pathfinder)
{
	pathfinder->DrawStart(renderer, m_Position);
	pathfinder->DrawEnd(renderer, m_Destination);

}
