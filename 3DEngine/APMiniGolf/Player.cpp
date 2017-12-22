//Includes
#include "Player.h"
#include "RenderEngine.h"


Player::Player(D3DEngine::RenderEngine* RenderEngine, D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, int PlayerID) :
	m_RenderEngine(RenderEngine), m_Ball(Ball), m_BallPhysics(BallPhysics), m_PlayerID(PlayerID)
{
	//Empty
}

Player::~Player()
{
	//Empty
}

void Player::SetBallStartPos(D3DEngine::Vector3f BallStartPos)
{
	//Store the initial Position of the ball
	m_BallStartPos = BallStartPos;
}

void Player::Active()
{
	//Set the ball back to the start position
	m_BallPhysics->SetPosition(m_BallStartPos);
	m_BallPhysics->SetVelocity(D3DEngine::Vector3f(0.0f, 0.0f, 0.0f));
}


void Player::Update(float Delta)
{
	//Get current balls velocity
	D3DEngine::Vector3f BallVel = m_BallPhysics->GetVelocity();
	//Check if ball is not moving
	if (BallVel == D3DEngine::Vector3f(0, 0, 0)) //Not Moving
	{
		//If it was previously moving, then increase the score by one
		if (m_WasMoving == true)
		{
			IncreaseScore();
			m_WasMoving = false;
		}
	}
	else //If ball was still moving set wasmoving to true
		m_WasMoving = true;
}

void Player::IncreaseScore()
{
	//Get Y offset for player
	int Y = 5 + (m_PlayerID * 24);
	//Increase Score for current level by 1
	m_Score++;
	std::string Text = "Player " + std::to_string(m_PlayerID) + ", Score: " + std::to_string(m_Score);
	//Update the UI
	std::string Name = "PLAYER" + std::to_string(m_PlayerID) + "SCORE";
	m_RenderEngine->AddText(Name, D3DEngine::TextToRender(Text, D3DEngine::Vector3f(255, 0, 255), 5, Y));
}