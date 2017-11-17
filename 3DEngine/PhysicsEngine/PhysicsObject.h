#pragma once

#include "Vector3f.h"

namespace D3DEngine
{
	class PhysicsObject
	{
	public:
		PhysicsObject(const Vector3f& Position, const Vector3f& Velocity);
		~PhysicsObject();

		void Integrate(float Delta);

		//Getters
		inline const Vector3f& GetPosition() const { return m_Position; }
		inline const Vector3f& GetVelocity() const { return m_Velocity; }

	private:
		Vector3f m_Position;
		Vector3f m_Velocity;
	};
}