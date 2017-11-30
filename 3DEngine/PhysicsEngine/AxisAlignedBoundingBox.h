#pragma once

#include "Vector3f.h"
#include "IntersectData.h"
#include "Collider.h"
#include "BoundingSphere.h"
#include <cmath>

namespace D3DEngine
{

	class AxisAlignedBoundingBox : public Collider
	{
	public:
		//AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents);
		AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents, Vector3f Center, Vector3f Dims, Vector2f Normal);
		~AxisAlignedBoundingBox();

		virtual void Transform(const Vector3f Translation);

		inline bool operator==(const AxisAlignedBoundingBox& Other) { return ((m_Center == Other.m_Center) && (m_Dims == Other.m_Dims)); }

		//Getters
		inline const Vector2f& GetNormal() const { return m_Normal; }
		inline const Vector3f& GetDims() const { return m_Dims; }
		inline const Vector3f& GetMinExtents() const { return m_MinExtents; }
		inline const Vector3f& GetMaxExtents() const { return m_MaxExtents; }
		virtual Vector3f GetCenter() const { return m_Center; }
		Vector3f& ClosestPoint(const Vector3f& point) const;
		Vector3f* ClosestPtPointAABB(const Vector3f& point) const;
	private:
		//Two Extreme Corners
		Vector3f m_MinExtents;	//Bottom left corner
		Vector3f m_MaxExtents;	//Top Right Corner

		Vector2f m_Normal;
		Vector3f m_Center;
		Vector3f m_Dims; //Holds the dimensions of the box
	};
}