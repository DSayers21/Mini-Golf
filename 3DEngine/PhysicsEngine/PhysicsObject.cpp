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
		//delete m_Collider;
	}

	void PhysicsObject::Integrate(float Delta)
	{
		ApplyFrictionForce(Delta);
		//Delta is time
		Vector3f VelocityDelta = (m_Velocity * Delta);
		m_Position = m_Position + VelocityDelta;
	}

	void PhysicsObject::ApplyFrictionForce(float Delta)
	{
		float gCoeffRestitution = 0.5f;
		float gCoeffFriction = 0.03f;
		float gGravityAccn = 9.8f;

		if (m_Velocity.Magnitude() <= 0.0) 
			return;

		//accelaration is opposite to direction of motion
		Vector3f accelaration = m_Velocity*-1;
		accelaration = accelaration.Normalise();
		//friction force = constant * mg
		//F=Ma, so accelaration = force/mass = constant*g
		accelaration = accelaration*(gCoeffFriction * gGravityAccn);
		//integrate velocity : find change in velocity
		Vector3f velocityChange = Vector3f(accelaration * Delta);
		velocityChange = velocityChange;
		//cap magnitude of change in velocity to remove integration errors
		if (velocityChange.Magnitude() > m_Velocity.Magnitude()) 
			m_Velocity.Set(0.0,0.0,0.0);
		else 
			m_Velocity = m_Velocity + velocityChange;
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