#pragma once
#include "PositionAABB.h"
#include "Colour.h"
#include "Renderer2D.h"
#include "Font.h"

class Button
{
public:
	
	// Default constructor
	Button();

	// Creates a button with a name, position and no colour or text

	Button(char* name, float xPos, float yPos, float width, float height);

	// Creates a button with a name, position, colour and no text

	Button(char* name, float xPos, float yPos, float width, float height, float red, float green, float blue, float alpha);

	// Creates a buttonwith a name, position, colour and text
	Button(char* name, float xPos, float yPos, float width, float height, float red, float green, float blue, float alpha, char* text);

	// Destructor
	~Button();

	//Returns the name of the button
	char* GetName();

	// Sets the name of the button
	void SetName(char* name);

	// Sets the Size of the button using floats
	void SetSizeAABB(float MinX, float MinY, float MaxX, float MaxY);

	// Sets the size using a struct
	void SetSizeAABB(PositionAABB* pos);

	// Returns the position as a struct
	PositionAABB* GetPosAABB();

	// Returns the width
	float GetWidth();

	// Returns the height
	float GetHeight();

	// Sets the  Min-Max for AABB
	void SetMinMax();

	// Returns the middle X position
	float GetXPos();

	// Sets the middle X position
	void SetXPos(float x);

	// Returns the middle Y position
	float GetYPos();

	//Sets the middle Y position
	void SetYPos(float y);

	// Returns the minimum X value
	float GetMinX();

	// Returns the minimum Y value
	float GetMinY();

	// Returns the maximum X value
	float GetMaxX();

	// Returns the maximum Y value
	float GetMaxY();

	// Sets the colour using a struct
	void SetColour(Colour* colour);

	// Sets the colour using floats
	void SetColour(float red, float green, float blue, float alpha);

	// Sets red 
	void SetRed(float red);

	// Sets green
	void SetGreen(float green);
	
	// Sets blue
	void SetBlue(float blue);

	// Sets alpha
	void SetAlpha(float alpha);

	// Draws the button
	void Draw(aie::Renderer2D* renderer, aie::Font* font);

	// Checks if the buttons presssed
	bool IsPressed(int x, int y);

private:

	// RGBA colour struct
	Colour* m_Colour;

	// MinX, MinY, MaxX, MaxY, position struct
	PositionAABB* m_Pos;

	// The name of the button
	char* m_Name;	

	// The buttons text
	char* m_Text;

	// The middle position of button
	float m_XPos, m_YPos;

	// Buttons width and height
	float m_Width, m_Height;
};

