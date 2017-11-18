#pragma once

#include "Vector3f.h"

namespace D3DEngine
{
	class IntersectData
	{
	public:
		IntersectData(const bool DoesIntersect, const Vector3f& Direction);
		~IntersectData();

		//Getters
		inline bool GetDoesIntersect() const { return m_DoesIntersect; }
		inline float GetDistance() const { return m_Direction.Length(); }
		inline const Vector3f& GetDirection() const { return m_Direction; }

	private:
		const bool m_DoesIntersect;
		const Vector3f m_Direction; //Store Direction, length is the distance
	};
}