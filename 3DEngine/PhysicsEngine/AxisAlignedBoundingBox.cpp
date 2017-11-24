#include "AxisAlignedBoundingBox.h"

namespace D3DEngine
{
	//AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f MinExtents, Vector3f MaxExtents) :
	//	Collider(Collider::TYPE_AABB), m_MinExtents(MinExtents), m_MaxExtents(MaxExtents)
	//{
	//}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3f Center, Vector3f Dims) :
		Collider(Collider::TYPE_AABB), m_Center(Center), m_Dims(Dims)
	{
		std::cerr << "AABB" << std::endl;
	}

	AxisAlignedBoundingBox::~AxisAlignedBoundingBox()
	{
	}

	IntersectData AxisAlignedBoundingBox::IntersectAABB(const AxisAlignedBoundingBox other) const
	{
		//Vector3f Distance1 = other.GetMinExtents().Sub(m_MaxExtents);
		//Vector3f Distance2 = m_MinExtents.Sub(other.GetMaxExtents());
		//Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
		////Get max component
		//float MaxDistance = Distance.Max();

		return IntersectData(2< 0, Vector3f(0,0,0));
	}

	IntersectData AxisAlignedBoundingBox::IntersectBoundingSphere(const BoundingSphere other) const
	{

		//Vector3f Distance1 = other.GetCenter().Sub(m_MaxExtents);
		//Vector3f Distance2 = m_MinExtents.Sub(other.GetCenter());

		//Vector3f Distance = Distance1.Max(Distance2);	//Get max x y and z components
		//												//Get max component
		//float MaxDistance = Distance.Max();
		//if(MaxDistance < other.GetRadius())
		//	std::cerr << "COLLISION1" << std::endl;

		return IntersectData(5235 < other.GetRadius(), Vector3f(0,0,0));
	}

	void AxisAlignedBoundingBox::Transform(const Vector3f Translation)
	{
		m_Center = m_Center + Translation;
	}

	Vector3f AxisAlignedBoundingBox::CalcCenter() const
	{
		//return Vector3f(
		//	((m_MaxExtents.GetX() + m_MinExtents.GetX()) / 2),
		//	((m_MaxExtents.GetY() + m_MinExtents.GetY()) / 2),
		//	((m_MaxExtents.GetZ() + m_MinExtents.GetZ()) / 2));
		return Vector3f();
	}
}