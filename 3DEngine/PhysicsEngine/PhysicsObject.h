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

		void Integrate(float Delta);

		//Getters
		inline const Vector3f& GetPosition() const { return m_Position; }
		inline const Vector3f& GetVelocity() const { return m_Velocity; }
		const Collider& GetCollider();

		//Setters
		inline void SetVelocity(const Vector3f& Velocity) { m_Velocity = Velocity; }

	private:
		Vector3f m_Position;
		Vector3f m_Velocity;
		Vector3f m_OldPosition;
		Collider* m_Collider;
	};
}