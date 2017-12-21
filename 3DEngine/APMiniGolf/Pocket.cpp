#include "Pocket.h"



Pocket::Pocket(D3DEngine::Vector3f Position, float Radius) :
	m_Position(Position), m_Radius(Radius)
{
}


Pocket::~Pocket()
{
}

bool Pocket::IsColliding(D3DEngine::PhysicsObject * Other)
{
	D3DEngine::Vector3f Result = Other->GetPosition() - m_Position;
	float Distance = Result.Length();
	
	if (Distance < m_Radius)//Add Velocity Check
		return true;

	return false;
}
