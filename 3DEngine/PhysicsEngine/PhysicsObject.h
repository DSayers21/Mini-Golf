#pragma once

#include "Vector3f.h"
#include "BoundingSphere.h"

namespace D3DEngine
{
	class PhysicsObject
	{
	public:
		PhysicsObject(const Vector3f& Position, const Vector3f& Velocity, float Radius);
		~PhysicsObject();

		void Integrate(float Delta);

		//Getters
		inline const Vector3f& GetPosition() const { return m_Position; }
		inline const Vector3f& GetVelocity() const { return m_Velocity; }
		inline float GetRadius() const { return m_Radius; }
		inline BoundingSphere GetBoundingSphere() const { return BoundingSphere(m_Position, m_Radius); }
		//Setters
		inline void SetVelocity(const Vector3f& Velocity) { m_Velocity = Velocity; }

	private:
		float m_Radius;
		Vector3f m_Position;
		Vector3f m_Velocity;
	};
}