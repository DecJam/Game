#include "Game2D.h"
#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

// Starts the game
Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2DRenderer = new aie::Renderer2D();

	// Initialise the font
	m_Font = new aie::Font("./font/consolas.ttf", 24);

	// Initialises the PaathFinder
	m_Pathfinder = new PathFinder();

	// Initialises the start node
	m_Start = new GridNode();

	// Initialises the end node
	m_End = new GridNode();

	// Sets the start and end node
	m_Start->placed = false;
	m_End->placed = false;
	
	//m_Agent = new Agent();
	// Sets the pathfinding type (temp)
	m_PathfindType = 2;

	// Creates a timer
	m_Timer = 0;
}

// Game's destructor
Game2D::~Game2D()
{/*
	delete m_Agent;
	m_Agent = nullptr;*/

	// Deletes the end node
	delete m_End;
	m_End = nullptr;

	// Deletes the start node
	delete m_Start;
	m_Start = nullptr;

	// Deletes the pathfinder
	delete m_Pathfinder;
	m_Pathfinder = nullptr;

	// Deletes the font
	delete m_Font;
	m_Font = nullptr;

	// Delete the renderer.
	delete m_2DRenderer;
	m_2DRenderer = nullptr;
}

// Game's update loop
void Game2D::Update(float deltaTime)
{
	// Updates the timer
	m_Timer += deltaTime;

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();

	// Sets the Camera
	float camPosX;
	float camPosY;
	m_2DRenderer->GetCameraPos(camPosX, camPosY);
	m_2DRenderer->SetCameraPos(camPosX, camPosY);


	// Places start point if LMB is pressed
	if  (input->IsMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		if ((input->GetMouseX()) >= (NODE_SIZE * GRID_SIZE) || (input->GetMouseY()) >= (NODE_SIZE * GRID_SIZE) || input->GetMouseX() < 0 || input->GetMouseY() < 0 || !m_Pathfinder->IsBlocked(input->GetMouseX() / NODE_SIZE, input->GetMouseY() / NODE_SIZE))
		{			
		}

		else
		{
			m_Start->position.x = input->GetMouseX() / NODE_SIZE;
			m_Start->position.y = input->GetMouseY() / NODE_SIZE;
			m_Start->placed = true;
		}
	}

	// Places end point if RMB is pressed
	if (input->IsMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		if (input->GetMouseX() >= (NODE_SIZE * GRID_SIZE) || (input->GetMouseY()) >= (NODE_SIZE * GRID_SIZE) || input->GetMouseX() < 0 || input->GetMouseY() < 0 || !m_Pathfinder->IsBlocked(input->GetMouseX() / NODE_SIZE, input->GetMouseY() / NODE_SIZE))
		{
		}

		else
		{
			m_End->position.x = input->GetMouseX() / NODE_SIZE;
			m_End->position.y = input->GetMouseY() / NODE_SIZE;
			m_End->placed = true;
		}
	}

	// Places blocked path if MMB is pressed
	if (input->IsMouseButtonDown(aie::INPUT_MOUSE_BUTTON_MIDDLE))
	{
		if (input->GetMouseX() >= (NODE_SIZE * GRID_SIZE) || (input->GetMouseY()) >= (NODE_SIZE * GRID_SIZE) || input->GetMouseX() < 0 || input->GetMouseY() < 0 || (input->GetMouseX() / NODE_SIZE) == m_End->position.x && (input->GetMouseY() / NODE_SIZE) == m_End->position.y || (input->GetMouseX() / NODE_SIZE) == m_Start->position.x && (input->GetMouseY() / NODE_SIZE) == m_Start->position.y)
		{	
		}

		else
		{
			int x = input->GetMouseX() / NODE_SIZE;
			int y = input->GetMouseY() / NODE_SIZE;
			m_Pathfinder->SetBlocked(x, y);
		}
	}

	m_Agent->Update(m_2DRenderer, m_Font);

	// Exit the application if ESCAPE is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

// Game's drawing
void Game2D::Draw()
{
	// Updates the instance
	aie::Application* application = aie::Application::GetInstance();

	// Retrieves the time
	float time = application->GetTime();
	
	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2DRenderer->Begin();

	// Renders the grid
	m_Pathfinder->DrawGrid(m_2DRenderer);

	// Draws the path beteen the start and the end node
	if (m_Start->placed == true && m_End->placed == true)
	{
		// Draws path
		m_Pathfinder->PathFind(m_2DRenderer, m_Start, m_End, m_PathfindType);
	}

	// Draws the start node
	m_Pathfinder->DrawStart(m_2DRenderer, m_Start);

	// Draws the end node
	m_Pathfinder->DrawEnd(m_2DRenderer, m_End);

	// Draws the agent
	m_Agent->Draw(m_2DRenderer, m_Font);

	//// Done drawing sprites. Must be called at the end of the Draw().
	m_2DRenderer->End();
}

void Game2D::TogglePathfindType()
{
	if (m_PathfindType == 1)
	{
		m_PathfindType = 2;
	}

	else
	{
		m_PathfindType = 1;
	}
}
