#pragma once

//Includes
#include <vector>

#include "GameComponent.h"
#include "GameObject.h"
#include "PhysicsObject.h"

//Forward Declaration
class RenderEngine;

class Player
{
public:
	//Constructor
	Player(D3DEngine::RenderEngine* RenderEngine, D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, int PlayerID);
	//Destructor
	~Player();
	//Set the balls starting position
	void SetBallStartPos(D3DEngine::Vector3f BallStartPos);
	//Set the player to being active
	void Active();
	//Update the player
	void Update(float Delta);
	//Increase the player's score
	void IncreaseScore();

	//Getters
	inline D3DEngine::PhysicsObject* GetBall() { return m_BallPhysics; }
	inline int GetScore() { return m_Score; }
	inline int GetID() { return m_PlayerID; }

private:
	//If the ball was previously moving
	bool m_WasMoving = false;
	int m_PlayerID = 0;		// Player Number, 1, 2, 3, etc
	int m_Score = -1;		//The score for each hole
	//Starting position of the ball
	D3DEngine::Vector3f m_BallStartPos;
	//Pointers To the Balls information
	D3DEngine::GameObject* m_Ball;
	D3DEngine::PhysicsObject* m_BallPhysics;
	//Pointer to the rendering engine
	D3DEngine::RenderEngine* m_RenderEngine;
};