#include "PhysicsObject.h"

namespace D3DEngine
{
	PhysicsObject::PhysicsObject(Collider* collider, const Vector3f& Velocity) :
		m_Position(collider->GetCenter()), m_Velocity(Velocity),
		m_OldPosition(collider->GetCenter()), m_Collider(collider)
	{
		m_Position = m_Position;
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

	void PhysicsObject::ApplyImpulse(Vector3f & velocity)
	{
		m_Velocity = velocity;
	}

	const Collider* PhysicsObject::GetCollider()
	{
		if (m_Position != m_OldPosition)
		{
			Vector3f Translation = m_Position - m_OldPosition;
			m_OldPosition = m_Position;
			m_Collider->Transform(Translation);
		}
		return m_Collider;
	}
}