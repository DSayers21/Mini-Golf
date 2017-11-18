#pragma once

#include "IntersectData.h"
#include <iostream>

namespace D3DEngine
{
	class Collider
	{
	public:
		enum
		{
			TYPE_SPHERE,
			TYPE_AABB,
			TYPE_SIZE
		};

		Collider(int Type);
		~Collider();

		IntersectData Intersect(const Collider& other) const;

		//Getters
		inline int GetType() const { return m_Type; }

	private:
		int m_Type;
	};
}