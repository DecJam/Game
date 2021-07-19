#include "Agent.h"

Agent::Agent()
{
	m_Start = new GridNode();
	m_End = new GridNode();
	m_Pathfinder = new PathFinder();
	m_Position = new Vector2();
	m_Destination = new Vector2();
	m_Position->x = 10;
	m_Position->y = 10;
	m_Destination->x = 100;
	m_Destination->y = 100;


	m_Start = m_Pathfinder->GetNodeByPos(m_Position->x, m_Position->y);
	m_End = m_Pathfinder->GetNodeByPos(m_Destination->x, m_Destination->y);
}

Agent::~Agent()
{
	delete m_Start;
	m_Start = nullptr;

	delete m_End;
	m_End = nullptr;
}

void Agent::Update(aie::Renderer2D* renderer, aie::Font* font)
{

	//FinalList = m_Pathfinder->GetFinalPath();
	//m_Start = FinalList[0];
}



void Agent::Draw(aie::Renderer2D* renderer, aie::Font* font)
{
	m_Pathfinder->PathFind(renderer, m_Start, m_End, 2);
	renderer->SetRenderColour(0, 255, 0, 255);
	renderer->DrawBox((m_Start->position.x * NODE_SIZE), (m_Start->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);

	renderer->SetRenderColour(255, 0, 0, 255);
	renderer->DrawBox((m_End->position.x * NODE_SIZE), (m_End->position.y * NODE_SIZE), NODE_SIZE * 0.9f, NODE_SIZE * 0.9f, 0.0f, 0.0f);
}
