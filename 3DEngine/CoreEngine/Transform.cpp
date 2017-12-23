//Includes
#include "Transform.h"
#include <iostream>
#include "Quaternion.h"

namespace D3DEngine
{
	Transform::Transform()
	{
		//Init Parent Matrix
		m_ParentMatrix = Matrix4f();
	}

	Transform::~Transform()
	{
		//Empty
	}

	Matrix4f Transform::GetTransformation() 
	{
		//Get Translation, rotation and scale
		Matrix4f Translation = Translation.InitTranslation(m_Position.GetX(), m_Position.GetY(), m_Position.GetZ());
		Matrix4f Rotation = m_Rotation.ToRotationMatrix();
		Matrix4f ScaleMatrix = ScaleMatrix.InitScaling(m_Scaling.GetX(), m_Scaling.GetY(), m_Scaling.GetZ());

		//Apply Rotation First
		return GetParentMatrix()->Mult((Translation.Mult(Rotation.Mult(ScaleMatrix))));
	}
	bool Transform::HasChanged()
	{
		//Check if there is a parent
		if (m_Parent != nullptr)
		{
			//Check if parent has changed
			bool parentHasChanged = m_Parent->HasChanged();
			if (parentHasChanged) 
				return true;
		}
		//Check if first time
		if (m_FirstTime)
		{	
			//Set previous to current
			m_PrevPosition.Set(m_Position);
			m_PrevRotation.Set(m_Rotation);
			m_PrevScaling.Set(m_Scaling);
			m_FirstTime = false;	//No longer first time
			return true;
		}

		if (m_Position != m_PrevPosition)		//Check if position is different to previous
			return true;
		if (m_Rotation != m_PrevRotation)		//Check if rotation is different to previous
			return true;
		if (m_Scaling != m_PrevScaling)			//Check if scale is different to previous
			return true;

		return false; //Return false (No change)
	}

	Vector3f Transform::GetTransformedPos()
	{
		//Return the transform
		return GetParentMatrix()->Transform(m_Position);
	}

	void Transform::Rotate(Vector3f Axis, float Angle)
	{
		//Update rotation, by angle
		m_Rotation = Quaternion(Axis, Angle).Mult(m_Rotation).Normalise();
	}
	
	void Transform::Update()
	{
		//Check if first time
		if (m_FirstTime)
		{
			//Init previous values
			m_PrevPosition = Vector3f();
			m_PrevRotation = Quaternion();
			m_PrevScaling = Vector3f();
		}
		else
		{
			//Update previous position, to being different
			m_PrevPosition = m_Position + Vector3f(1, 1, 1);
			m_PrevRotation.SetX(m_Rotation.GetX() + 120);
			m_PrevScaling = m_Scaling * 12;
			m_FirstTime = false;
		}
	}

	Quaternion Transform::GetTransformedRot()
	{
		//Setup parent rotation
		Quaternion parentRotation = Quaternion(0,0,0,1);

		//Check if there is a parent
		if (m_Parent != nullptr)
			parentRotation = m_Parent->GetTransformedRot();	//Update the rotation

		//Return the full rotation after accounting for all parents
		return parentRotation.Mult(m_Rotation);
	}

	Matrix4f* Transform::GetParentMatrix()
	{
		//Check if there is a parent, and it has changed
		if ((m_Parent != nullptr) && (m_Parent->HasChanged()))
		{
			//Get parent transformation
			m_ParentMatrix = m_Parent->GetTransformation();
			//Update previous data to current
			m_PrevPosition.Set(m_Position);
			m_PrevRotation.Set(m_Rotation);
			m_PrevScaling.Set(m_Scaling);
		}
		//Return parent matrix
		return &m_ParentMatrix;
	}

	Transform::Transform(const Transform &other) 
	{
		//Display Message
		std::cerr << "Copied" << std::endl;

		//Set all values to those of the other transform
		m_Position = other.m_Position;
		m_Rotation = other.m_Rotation;
		m_Scaling = other.m_Scaling;
		m_FirstTime = other.m_FirstTime;
		m_PrevPosition = other.m_PrevPosition;
		m_PrevRotation = other.m_PrevRotation;
		m_PrevScaling = other.m_PrevScaling;
		m_Parent = other.m_Parent;
		m_ParentMatrix = other.m_ParentMatrix;
		m_FirstTime = other.m_FirstTime;
	}

	Transform& Transform::operator=(const Transform &other)
	{
		//Set all values to those of the other transform
		m_Position = other.m_Position;
		m_Rotation = other.m_Rotation;
		m_Scaling = other.m_Scaling;
		m_FirstTime = other.m_FirstTime;
		m_PrevPosition = other.m_PrevPosition;
		m_PrevRotation = other.m_PrevRotation;
		m_PrevScaling = other.m_PrevScaling;
		m_Parent = other.m_Parent;
		m_ParentMatrix = other.m_ParentMatrix;
		m_FirstTime = other.m_FirstTime;
		//Return this transform
		return *this;
	}
}