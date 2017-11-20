#include "Collider.h"
#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"
#include "Plane.h"

namespace D3DEngine
{
	Collider::Collider(int Type) :
		m_Type(Type)
	{
	}


	Collider::~Collider()
	{
	}

	IntersectData Collider::Intersect(const Collider & other) const
	{
		if ((m_Type == TYPE_SPHERE) && (other.GetType() == TYPE_SPHERE))
		{
			//Cast self to be a bounding sphere
			BoundingSphere* self = (BoundingSphere*)this;
			return self->IntersectBoundingSphere((BoundingSphere&)other);
		}
		if ((m_Type == TYPE_SPHERE) && (other.GetType() == TYPE_AABB))
		{
			//Cast self to be a bounding sphere
			BoundingSphere* self = (BoundingSphere*)this;
			return self->IntersectAABB((AxisAlignedBoundingBox&)other);
		}

		if ((m_Type == TYPE_AABB) && (other.GetType() == TYPE_SPHERE))
		{
			//Cast self to be a AxisAlignedBoundingBox
			AxisAlignedBoundingBox* self = (AxisAlignedBoundingBox*)this;
			return self->IntersectBoundingSphere((BoundingSphere&)other);
		}

		if ((m_Type == TYPE_AABB) && (other.GetType() == TYPE_AABB))
		{
			//Cast self to be a AxisAlignedBoundingBox
			AxisAlignedBoundingBox* self = (AxisAlignedBoundingBox*)this;
			return self->IntersectAABB((AxisAlignedBoundingBox&)other);
		}

		std::cerr << "Error: Collisions not implemented between specified colliders." << std::endl;
		//This point should never be reached
		return IntersectData(false, Vector3f(0,0,0));
	}
}