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
		AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents);
		~AxisAlignedBoundingBox();

		IntersectData IntersectAABB(const AxisAlignedBoundingBox other) const;
		IntersectData IntersectBoundingSphere(const BoundingSphere other) const;

		virtual void Transform(const Vector3f Translation);

		//Getters
		inline const Vector3f& GetMinExtents() const { return m_MinExtents; }
		inline const Vector3f& GetMaxExtents() const { return m_MaxExtents; }

	private:
		//Two Extreme Corners
		const Vector3f m_MinExtents;	//Bottom left corner
		const Vector3f m_MaxExtents;	//Top Right Corner
	};
}