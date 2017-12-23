//Includes
#include "Collider.h"
#include "BoundingSphere.h"
#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	Collider::Collider(int Type) :
		m_Type(Type)
	{
		//Empty
	}

	Collider::~Collider()
	{
		//Empty
	}

	IntersectData* Collider::Intersect(const Collider & other) const
	{
		//Check if the collision is between a sphere and a AABB
		if ((m_Type == TYPE_SPHERE) && (other.GetType() == TYPE_AABB))
		{
			//Cast self to be a bounding sphere
			BoundingSphere* self = (BoundingSphere*)this;
			//Intersect a AABB
			return self->IntersectAABB((AxisAlignedBoundingBox&)other);
		}
		//Can add more collision types e.g. sphere and sphere etc

		//This point should never be reached if all collisions are handled
		return new IntersectData(false, Vector3f(0,0,0));
	}
}