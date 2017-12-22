#pragma once

//Includes
#include "Vector3f.h"
#include "PhysicsObject.h"
#include <iostream>

class Pocket
{
public:
	//Constructor
	Pocket(D3DEngine::Vector3f Position, float Radius);
	//Destructor
	~Pocket();
	//Check if pocket is colliding with ball
	bool IsColliding(D3DEngine::PhysicsObject* Other);

private:
	//Position of the pocket
	D3DEngine::Vector3f m_Position;
	//Radius of the pocket
	float m_Radius;
};