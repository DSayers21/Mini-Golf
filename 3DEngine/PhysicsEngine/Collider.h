#pragma once

//Includes
#include "Vector3f.h"
#include "IntersectData.h"
#include <iostream>

namespace D3DEngine
{
	class Collider
	{
	public:
		//Enum to manage the type of collider being used
		enum
		{
			TYPE_SPHERE,
			TYPE_AABB,
			TYPE_SIZE
		};

		//Constructor
		Collider(int Type);
		//Destructor
		~Collider();

		//Intersect with another collider
		IntersectData* Intersect(const Collider& other) const;
		//Transform the colliders position
		virtual void Transform(const Vector3f Translation) {};
		
		//Getters
		inline int GetType() const { return m_Type; }
		inline virtual Vector3f GetCenter() const { return Vector3f(0, 0, 0); }

	private:
		//The type of collider
		int m_Type;
	};
}