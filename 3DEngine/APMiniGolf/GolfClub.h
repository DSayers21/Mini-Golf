#pragma once

#include "GameComponent.h"
#include "GameObject.h"
#include "PhysicsObject.h"

class GolfClub : public D3DEngine::GameComponent
{
public:
	GolfClub(D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, float MaxDist, float DisIncrement, float RotIncrement);
	~GolfClub();
	virtual void Input(D3DEngine::GetInput* input, float Delta);
	virtual void Update(float Delta);

private:
	D3DEngine::GameObject* m_Ball;
	D3DEngine::PhysicsObject* m_BallPhysics;

	float m_Distance = 0.0f;
	float m_MaxDist = 0.0f;
	float m_DisIncrement = 0.0f;

	float m_Rotation = 0.0f;
	float m_RotIncrement = 0.0f;
};
