#pragma once

#include "Vector3f.h"
#include "BoundingSphere.h"

namespace D3DEngine
{
	class PhysicsObject
	{
	public:
		PhysicsObject(Collider* collider, const Vector3f& Velocity);
		~PhysicsObject();
		void DeleteCollider() { delete m_Collider; }

		void Integrate(float Delta);

		void ApplyFrictionForce(float Delta);

		void ApplyImpulse(Vector3f& velocity);

		//Getters
		inline const Vector3f& GetPosition() const { return m_Position; }
		inline const Vector3f& GetVelocity() const { return m_Velocity; }
		const Collider* GetCollider();

		//Setters
		inline void SetPosition(const Vector3f& Position) { m_Position = Position; }
		inline void SetVelocity(const Vector3f& Velocity) { m_Velocity = Velocity; }

	private:
		Vector3f m_Position;
		Vector3f m_Velocity;
		Vector3f m_OldPosition;
		Collider* m_Collider;
	};
}