#pragma once

#include "Vector3f.h"
#include "IntersectData.h"
#include "Collider.h"
#include "BoundingSphere.h"


namespace D3DEngine
{

	class AxisAlignedBoundingBox : public Collider
	{
	public:
		//AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents);
		AxisAlignedBoundingBox(Vector3f Center, Vector3f Dims);
		~AxisAlignedBoundingBox();

		IntersectData IntersectAABB(const AxisAlignedBoundingBox other) const;
		IntersectData IntersectBoundingSphere(const BoundingSphere other) const;

		virtual void Transform(const Vector3f Translation);

		//Getters
		inline const Vector3f& GetDims() const { return m_Dims; }
		//inline const Vector3f& GetMinExtents() const { return m_MinExtents; }
		//inline const Vector3f& GetMaxExtents() const { return m_MaxExtents; }
		virtual Vector3f GetCenter() const { return m_Center; }
		Vector3f CalcCenter() const;
	private:
		//Two Extreme Corners
		//Vector3f m_MinExtents;	//Bottom left corner
		//Vector3f m_MaxExtents;	//Top Right Corner

		Vector3f m_Center;
		Vector3f m_Dims; //Holds the dimensions of the box
	};
}