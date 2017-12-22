#pragma once

//Includes
#include "GameComponent.h"
#include "GameObject.h"
#include "PhysicsObject.h"

//Inherit from GameComponent
class GolfClub : public D3DEngine::GameComponent
{
public:
	//Constructor and Destructor
	GolfClub(D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, float MaxDist, float DisIncrement, float RotIncrement);
	~GolfClub();
	//Get Input for the club
	virtual void Input(D3DEngine::GetInput* input, float Delta);
	//Update the club
	virtual void Update(float Delta);

private:
	//Pointers to the ball and the balls physics
	D3DEngine::GameObject* m_Ball;
	D3DEngine::PhysicsObject* m_BallPhysics;

	float m_Distance = 0.0f;				//Current distance from the ball
	float m_MaxDist = 0.0f;					//Max distance allowed from the ball
	float m_DisIncrement = 0.0f;			//The amount the distance gets incremented each time

	float m_Rotation = 0.0f;				//Current rotation around the ball
	float m_RotIncrement = 0.0f;			//The amount the rotation gets incremented each time
};