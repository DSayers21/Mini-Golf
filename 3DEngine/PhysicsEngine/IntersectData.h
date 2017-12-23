#pragma once

//Includes
#include "Vector3f.h"

namespace D3DEngine
{
	class IntersectData
	{
	public:
		//Constructor
		IntersectData(const bool DoesIntersect, const Vector3f& Direction);
		//Destructor
		~IntersectData();

		//Getters
		inline bool GetDoesIntersect() const { return m_DoesIntersect; }
		inline float GetDistance() const { return m_Direction.Length(); }
		inline const Vector3f& GetDirection() const { return m_Direction; }

	private:
		const bool m_DoesIntersect;	//If the intersect did happen
		const Vector3f m_Direction; //Store Direction, length is the distance
	};
}