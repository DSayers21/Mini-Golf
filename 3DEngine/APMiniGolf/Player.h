#pragma once

#include <vector>

#include "GameComponent.h"
#include "GameObject.h"
#include "PhysicsObject.h"

class RenderEngine;

class Player
{
public:
	Player(D3DEngine::RenderEngine* RenderEngine, D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, int PlayerID);
	~Player();

	void SetBallStartPos(D3DEngine::Vector3f BallStartPos);

	void Active();

	void Update(float Delta);

	void IncreaseScore();

	inline D3DEngine::PhysicsObject* GetBall() { return m_BallPhysics; }
	inline int GetScore() { return m_Score; }
	inline int GetID() { return m_PlayerID; }

private:
	bool m_WasMoving = false;
	int m_PlayerID = 0; // Player Number, 1, 2, 3, etc
	int m_Score = -1; //The score for each hole
	D3DEngine::Vector3f m_BallStartPos;
	//Pointers To the Ball
	D3DEngine::GameObject* m_Ball;
	D3DEngine::PhysicsObject* m_BallPhysics;
	D3DEngine::RenderEngine* m_RenderEngine;
};

