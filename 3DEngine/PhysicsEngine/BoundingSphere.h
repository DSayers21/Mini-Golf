#pragma once

//Includes
#include "Vector3f.h"
#include "IntersectData.h"
#include "Collider.h"

namespace D3DEngine
{
	//Forward Declaration
	class AxisAlignedBoundingBox;

	//Inherit from Collider
	class BoundingSphere : public Collider
	{
	public:
		//Constructor
		BoundingSphere(Vector3f Center, float Radius);
		//Destructor
		~BoundingSphere();

		//Intersect With another bounding Sphere
		IntersectData* IntersectBoundingSphere(const BoundingSphere& other);
		//Intersect With an AABB
		IntersectData* IntersectAABB(const AxisAlignedBoundingBox& other);

		//Transform the spheres position
		virtual void Transform(const Vector3f Translation);
		
		//Getters
		inline virtual Vector3f GetCenter() const { return m_Center; }
		inline float GetRadius() const { return m_Radius; }
	private:
		Vector3f m_Center;	//Centre pos of sphere
		float m_Radius;		//Radius of sphere
	};	
}