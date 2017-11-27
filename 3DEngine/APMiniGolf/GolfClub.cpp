#include "GolfClub.h"



GolfClub::GolfClub(D3DEngine::GameObject* Ball, D3DEngine::PhysicsObject* BallPhysics, float MaxDist, float DisIncrement, float RotIncrement)
{
	m_Ball = Ball;
	m_BallPhysics = BallPhysics;
	m_MaxDist = MaxDist;
	m_DisIncrement = DisIncrement;
	m_RotIncrement = RotIncrement;
}


GolfClub::~GolfClub()
{
}

void GolfClub::Input(D3DEngine::GetInput* input, float Delta)
{
	D3DEngine::Vector3f BallPos = *m_Ball->GetTransform()->GetPosition();

	if (input->GetKeyDown(D3DEngine::KEY_R))
	{
		m_BallPhysics->ApplyImpulse(D3DEngine::Vector3f(0,0,0));
		m_BallPhysics->SetPosition(D3DEngine::Vector3f(0, 0, 0));
		m_Parent->SetVisible(true);
		m_Parent->SetActive(true);
	}

	//Rotation
	if (input->GetKeyDown(D3DEngine::KEY_LEFT))
	{
		m_Rotation += TO_RADIANS(m_RotIncrement);
		m_Ball->GetTransform()->Rotate(m_Ball->GetTransform()->GetRotation()->GetDown()*-1, TO_RADIANS(m_RotIncrement));
	}

	if (input->GetKeyDown(D3DEngine::KEY_RIGHT))
	{
		m_Rotation -= TO_RADIANS(m_RotIncrement);
		m_Ball->GetTransform()->Rotate(m_Ball->GetTransform()->GetRotation()->GetDown()*-1, TO_RADIANS(-m_RotIncrement));
	}
	//End Rotation

	//Increase Power/Dist to ball
	if (input->GetKeyDown(D3DEngine::KEY_UP))
	{
		if (m_Distance + 1 <= m_MaxDist)
		{
			m_Distance += 1;
			m_Parent->GetTransform()->GetPosition()->SetX(m_Parent->GetTransform()->GetPosition()->GetX() - m_DisIncrement);
		}
	}
	if (input->GetKeyDown(D3DEngine::KEY_DOWN))
	{
		if (m_Distance - 1 >= 0)
		{
			m_Distance -= 1;
			m_Parent->GetTransform()->GetPosition()->SetX(m_Parent->GetTransform()->GetPosition()->GetX() + m_DisIncrement);
		}
	}
	//End Increase Power/Dist to ball
	//HitBall
	if (input->GetKeyDown(D3DEngine::KEY_SPACE))
	{
		m_Parent->SetVisible(false);
		m_Parent->SetActive(false);

		float CueAngle = m_Rotation;
		float CuePower = m_Distance/10.0f;
		float CueBallFactor = 8.0;

		float x = (cosf(CueAngle) * CuePower * CueBallFactor);
		float z = (-sinf(CueAngle) * CuePower * CueBallFactor);

		D3DEngine::Vector3f Impulse(x, 0, z);

		m_BallPhysics->ApplyImpulse(Impulse);
	}
	//End HitBall
}

void GolfClub::Update(float Delta)
{
	D3DEngine::Vector3f BallVel = m_BallPhysics->GetVelocity();
	if (BallVel == D3DEngine::Vector3f(0, 0, 0))
	{
		m_Parent->SetVisible(true);
		m_Parent->SetActive(true);
	}
}