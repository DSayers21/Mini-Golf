#pragma once

#include "Vector3f.h"
#include "IntersectData.h"
#include "BoundingSphere.h"

namespace D3DEngine
{
	class Plane
	{
	public:
		Plane(const Vector3f& Normal, float Distance);
		~Plane();

		Plane Normalise() const;
		IntersectData IntersectSphere(const BoundingSphere& other) const;

		//Getters
		inline const Vector3f& GetNormal() const { return m_Normal; }
		inline float GetDistance() const { return m_Distance; }

	private:
		const Vector3f m_Normal;
		const float m_Distance;
	};
}