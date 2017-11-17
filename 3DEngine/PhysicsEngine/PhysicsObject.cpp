#include "PhysicsObject.h"

namespace D3DEngine
{
	PhysicsObject::PhysicsObject(const Vector3f& Position, const Vector3f& Velocity) :
		m_Position(Position), m_Velocity(Velocity)
	{
	}


	PhysicsObject::~PhysicsObject()
	{
	}

	void PhysicsObject::Integrate(float Delta)
	{
		//Delta is time
		Vector3f VelocityDelta = m_Velocity * Delta;
		m_Position = m_Position + VelocityDelta;
	}
}