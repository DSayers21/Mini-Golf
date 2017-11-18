#pragma once

#include "Vector3f.h"
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
		virtual void Transform(const Vector3f Translation) {};
		virtual Vector3f GetCenter() const { return Vector3f(0, 0, 0); }

		//Getters
		inline int GetType() const { return m_Type; }

	private:
		int m_Type;
	};
}