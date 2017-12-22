//Includes
#include "GolfClub.h"

//Constructor sets all variables up
GolfClub::GolfClub(D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, float MaxDist, float DisIncrement, float RotIncrement) :
	m_Ball(Ball), m_BallPhysics(BallPhysics),
	m_MaxDist(MaxDist), m_DisIncrement(DisIncrement), 
	m_RotIncrement(RotIncrement)
{
	//empty
}

//Destructor
GolfClub::~GolfClub()
{
	//empty
}

void GolfClub::Input(D3DEngine::GetInput* input, float Delta)
{
	//Get the current position of the ball
	D3DEngine::Vector3f BallPos = *m_Ball->GetTransform()->GetPosition();

	//Check if key left is pressed
	if (input->GetKeyDown(D3DEngine::KEY_LEFT))
	{
		//Rotate the club around the ball
		m_Rotation += TO_RADIANS(m_RotIncrement);
		m_Ball->GetTransform()->Rotate(m_Ball->GetTransform()->GetRotation()->GetDown()*-1, TO_RADIANS(m_RotIncrement));
	}
	//Check if key right is pressed
	if (input->GetKeyDown(D3DEngine::KEY_RIGHT))
	{
		//Rotate the club around the ball
		m_Rotation -= TO_RADIANS(m_RotIncrement);
		m_Ball->GetTransform()->Rotate(m_Ball->GetTransform()->GetRotation()->GetDown()*-1, TO_RADIANS(-m_RotIncrement));
	}
	//End Rotation

	//Check if up key is pressed
	if (input->GetKeyDown(D3DEngine::KEY_UP))
	{
		//Increase distance by increment
		if (m_Distance + m_DisIncrement <= m_MaxDist)
		{
			m_Distance += m_DisIncrement;
			m_Parent->GetTransform()->GetPosition()->SetX(m_Parent->GetTransform()->GetPosition()->GetX() - m_DisIncrement);
		}
	}
	//Check if down key is pressed
	if (input->GetKeyDown(D3DEngine::KEY_DOWN))
	{
		//Descrease distance by increment
		if (m_Distance - m_DisIncrement >= 0)
		{
			m_Distance -= m_DisIncrement;
			m_Parent->GetTransform()->GetPosition()->SetX(m_Parent->GetTransform()->GetPosition()->GetX() + m_DisIncrement);
		}
	}
	//End Increase Power/Dist to ball
	//Check is space key is pressed
	if (input->GetKeyDown(D3DEngine::KEY_SPACE))
	{
		//Make golf club in visible and inactive
		m_Parent->SetVisible(false);
		m_Parent->SetActive(false);

		//Get the angle of the club
		float clubAngle = m_Rotation;
		//Get the power of the club
		float clubPower = m_Distance/10.0f;
		float clubBallFactor = 8.0;

		float x = (cosf(clubAngle) * clubPower * clubBallFactor);	//Work out the x component of the impulse
		float z = (-sinf(clubAngle) * clubPower * clubBallFactor);	//Work out the z component of the impulse
		
		//Apply the impulse
		m_BallPhysics->ApplyImpulse(D3DEngine::Vector3f(x, 0, z));
	}
	//End HitBall
}

void GolfClub::Update(float Delta)
{
	//Get the current ball velocity
	D3DEngine::Vector3f BallVel = m_BallPhysics->GetVelocity();
	//Check if the velocity is 0
	if (BallVel == D3DEngine::Vector3f(0, 0, 0))
	{
		//Make the golf club both active and visible
		m_Parent->SetVisible(true);
		m_Parent->SetActive(true);
	}
}