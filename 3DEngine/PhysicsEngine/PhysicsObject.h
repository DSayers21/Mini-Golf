#pragma once

//Includes
#include "Vector3f.h"
#include "BoundingSphere.h"

namespace D3DEngine
{
	class PhysicsObject
	{
	public:
		//Constructor
		PhysicsObject(Collider* collider, const Vector3f& Velocity);
		//Destructor
		~PhysicsObject();

		//Integrate the physics object (update)s
		void Integrate(float Delta);

		//Apply Friction to the physics object
		void ApplyFrictionForce(float Delta);
		//Apply impulse to the physics object
		void ApplyImpulse(Vector3f& velocity);

		//Getters
		inline const Vector3f& GetPosition() const { return m_Position; }
		inline const Vector3f& GetVelocity() const { return m_Velocity; }
		const Collider* GetCollider();

		//Setters
		inline void SetPosition(const Vector3f& Position) { m_Position = Position; }
		inline void SetVelocity(const Vector3f& Velocity) { m_Velocity = Velocity; }

	private:
		Vector3f m_Position;		//Position of physics object
		Vector3f m_Velocity;		//Velocity of physics object
		Vector3f m_OldPosition;		//Old Position of physics object
		Collider* m_Collider;		//Pointer to Collider of physics object
	};
}