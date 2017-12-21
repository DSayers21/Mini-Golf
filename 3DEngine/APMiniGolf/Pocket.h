#pragma once

#include "Vector3f.h"
#include "PhysicsObject.h"
#include <iostream>

class Pocket
{
public:
	Pocket(D3DEngine::Vector3f Position, float Radius);
	~Pocket();

	bool IsColliding(D3DEngine::PhysicsObject* Other);

private:
	D3DEngine::Vector3f m_Position;
	float m_Radius;
};