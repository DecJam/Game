#include "Button.h"
#include <iostream>
#define NAME_LENGTH 20
#define TEXT_LENGTH 100

// Creates a default button
Button::Button()
{
	m_Name = new char[NAME_LENGTH];
	m_Text = new char[TEXT_LENGTH];
	m_Colour = new Colour();
	m_Pos = new PositionAABB();

	strcpy_s(m_Name, NAME_LENGTH, "Button");

	m_XPos = 850;
	m_YPos = 650;
	m_Width = 150;
	m_Height = 50;
	SetMinMax();

	m_Colour->Red = 255;
	m_Colour->Blue = 255;
	m_Colour->Green = 255;
	m_Colour->Alpha = 1;

	strcpy_s(m_Text, TEXT_LENGTH, "Default");
}

// Creates a button with a name, position and no colour or text
Button::Button(char* name, float xPos, float yPos, float width, float height)
{
	m_Name = new char[NAME_LENGTH];
	m_Text = new char[TEXT_LENGTH];
	m_Colour = new Colour();
	m_Pos = new PositionAABB();

	strcpy_s(m_Name, NAME_LENGTH, name);
	
	m_XPos = xPos;
	m_YPos = yPos;
	m_Width = width;
	m_Height = height;
	SetMinMax();

	m_Colour->Red = 255.0f;
	m_Colour->Blue = 255.0f;
	m_Colour->Green = 255.0f;
	m_Colour->Alpha = 1.0f;

	m_Text[0] = 0;
}

// Creates a button with a name, position, colour and no text
Button::Button(char* name, float xPos, float yPos, float width, float height, float red, float green, float blue, float alpha)
{
	m_Name = new char[NAME_LENGTH];
	m_Text = new char[TEXT_LENGTH];
	m_Colour = new Colour();
	m_Pos = new PositionAABB();

	strcpy_s(m_Name, NAME_LENGTH, name);

	m_XPos = xPos;
	m_YPos = yPos;
	m_Width = width;
	m_Height = height;
	SetMinMax();

	m_Colour->Red = red;
	m_Colour->Blue = green;
	m_Colour->Green = blue;
	m_Colour->Alpha = alpha;

	m_Text[0] = 0;
}

// Creates a buttonwith a name, position, colour and text
Button::Button(char* name, float xPos, float yPos, float width, float height, float red, float green, float blue, float alpha, char* text)
{
	m_Name = new char[NAME_LENGTH];
	m_Text = new char[TEXT_LENGTH];
	m_Colour = new Colour();
	m_Pos = new PositionAABB();
	strcpy_s(m_Name, NAME_LENGTH, name);

	m_XPos = xPos;
	m_YPos = yPos;
	m_Width = width;
	m_Height = height;
	SetMinMax();

	m_Colour->Red = red;
	m_Colour->Blue = green;
	m_Colour->Green = blue;
	m_Colour->Alpha = alpha;

	strcpy_s(m_Text, NAME_LENGTH, text);
}

// Button's destructor
Button::~Button()
{
	delete[] m_Name;
	m_Name = nullptr;

	delete[] m_Text;
	m_Text = nullptr;

	delete m_Pos;
	m_Pos = nullptr;

	delete m_Colour;
	m_Colour = nullptr;
}

// Returns the name of the button
char* Button::GetName()
{
	return m_Name;
}

// Sets the name of the button
void Button::SetName(char* name)
{
	strcpy_s(m_Name, NAME_LENGTH, name);
}

// Sets the AABB size of the button using floats
void Button::SetSizeAABB(float MinX, float MinY, float MaxX, float MaxY)
{
	m_Pos->minX = MinX;
	m_Pos->minY = MinY;
	m_Pos->maxX = MaxX;
	m_Pos->maxY = MaxY;
}

// Sets the AABB size of the button using a struct
void Button::SetSizeAABB(PositionAABB* pos)
{
	m_Pos = pos;
}

// Returns the AABB positions in a struct
PositionAABB* Button::GetPosAABB()
{
	return m_Pos;
}

// Returns the width of the button
float Button::GetWidth()
{
	return m_Width;
}

// Returns the height of the button
float Button::GetHeight()
{
	return m_Height;
}

// Sets the AABB/ Min-Max from the x,y positions and height,width
void Button::SetMinMax()
{
	m_Pos->maxX = m_XPos + (0.5f * m_Width);
	m_Pos->maxY = m_YPos + (0.5f * m_Height);
	m_Pos->minX = m_XPos - (0.5f * m_Width);
	m_Pos->minY = m_YPos - (0.5f * m_Height);
}

// Returns the middle X position
float Button::GetXPos()
{
	return m_XPos;
}

// Sets the middle X position
void Button::SetXPos(float x)
{
	m_XPos = x;
}

// Returns the middle Y position
float Button::GetYPos()
{
	return m_YPos;
}

// Sets the middle Y position
void Button::SetYPos(float y)
{
	m_YPos = y;
}

// Returns MinX from AABB
float Button::GetMinX()
{
	return m_Pos->minX;
}

// Returns MinY from AABB
float Button::GetMinY()
{
	return m_Pos->minY;
}

// Returns MaxX from AABB
float Button::GetMaxX()
{
	return m_Pos->maxX;
}

// Returns MaxY from AABB
float Button::GetMaxY()
{
	return m_Pos->maxY;
}

// Sets the buttons colour using a struct
void Button::SetColour(Colour* colour)
{
	m_Colour = colour;
}

// Sets the buttins colour using floats
void Button::SetColour(float red, float green, float blue, float alpha)
{
	m_Colour->Red = red;
	m_Colour->Green = green;
	m_Colour->Blue = blue;
	m_Colour->Alpha = alpha;
}

// Sets the buttons red value
void Button::SetRed(float red)
{
	m_Colour->Red = red;
}

// Sets the buttons green value
void Button::SetGreen(float green)
{
	m_Colour->Green = green;
}

// Sets the buttons blue value
void Button::SetBlue(float blue)
{
	m_Colour->Blue = blue;
}

// Sets the buttons alpha value
void Button::SetAlpha(float alpha)
{
	m_Colour->Alpha = alpha;
}

// Draws the button with its text
void Button::Draw(aie::Renderer2D* renderer, aie::Font* font)
{
	renderer->SetRenderColour(m_Colour->Red, m_Colour->Green, m_Colour->Blue, 1.0f);
	renderer->DrawBox( m_XPos, m_YPos, m_Width, m_Height, 0.0f, 0.0f);

	renderer->SetRenderColour(0, 0, 0, 1.0f);
	renderer->DrawText2D(font, m_Text, m_Pos->minX, m_YPos, 0.0f);
}

// Checks if the button is pressed
bool Button::IsPressed(int x, int y)
{
	if (x >= m_Pos->minX && x <= m_Pos->maxX && y >= m_Pos->minY && y <= m_Pos->maxY)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}
