//Includes
#include "PhysicsObject.h"

namespace D3DEngine
{
	PhysicsObject::PhysicsObject(Collider* collider, const Vector3f& Velocity) :
		m_Position(collider->GetCenter()), m_Velocity(Velocity),
		m_OldPosition(collider->GetCenter()), m_Collider(collider)
	{
		//Empty
	}

	PhysicsObject::~PhysicsObject()
	{
		//Display message
		std::cerr << "Destructor: Physics Object" << std::endl;
		//Delete the collider
		delete m_Collider;
	}

	void PhysicsObject::Integrate(float Delta)
	{
		//Apply the friction force to the physics object
		ApplyFrictionForce(Delta);
		//Delta is time, update velocity based on delta
		Vector3f VelocityDelta = (m_Velocity * Delta);
		m_Position = m_Position + VelocityDelta;
	}

	void PhysicsObject::ApplyFrictionForce(float Delta)
	{
		//Physics forces
		float gCoeffRestitution = 0.5f;
		float gCoeffFriction = 0.03f;
		float gGravityAccn = 9.8f;

		//Check if the magnitude of the velocity is less than or equal to 0
		if (m_Velocity.Magnitude() <= 0.0) 
			return;

		//Accelaration is opposite to direction of motion
		Vector3f accelaration = m_Velocity*-1;
		accelaration = accelaration.Normalise();
		//Friction force = constant * mg
		//F=Ma, so accelaration = force/mass = constant*g
		accelaration = accelaration*(gCoeffFriction * gGravityAccn);
		//Integrate velocity : find change in velocity
		Vector3f velocityChange = Vector3f(accelaration * Delta);
		velocityChange = velocityChange;
		//Cap magnitude of change in velocity to remove integration errors
		if (velocityChange.Magnitude() > m_Velocity.Magnitude()) 
			m_Velocity.Set(0.0,0.0,0.0);
		else 
			m_Velocity = m_Velocity + velocityChange;
	}

	void PhysicsObject::ApplyImpulse(Vector3f & velocity)
	{
		//Make the velocity equal the impulse velocity passed in
		m_Velocity = velocity;
	}

	const Collider* PhysicsObject::GetCollider()
	{
		//Check if the position is different to the old position
		if (m_Position != m_OldPosition)
		{
			//Calculate the translation between the old and new positions
			Vector3f Translation = m_Position - m_OldPosition;
			//Update the old position
			m_OldPosition = m_Position;
			//Transform the colliders position
			m_Collider->Transform(Translation);
		}
		//Return the collider
		return m_Collider;
	}
}