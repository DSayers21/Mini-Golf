//Includes
#include "Pocket.h"

Pocket::Pocket(D3DEngine::Vector3f Position, float Radius) :
	m_Position(Position), m_Radius(Radius)
{
	//Empty
}

Pocket::~Pocket()
{
	//Empty
}

bool Pocket::IsColliding(D3DEngine::PhysicsObject * Other)
{
	//Get the distance between the pocket and the ball
	D3DEngine::Vector3f Result = Other->GetPosition() - m_Position;
	float Distance = Result.Length();
	//Check if the distance is within the pockets radius
	if (Distance < m_Radius)
		return true;	//return true (ball is in the pocket)

	return false;	//return false (ball is not in the pocket)
}