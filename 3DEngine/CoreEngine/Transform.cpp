#include "Transform.h"
#include <iostream>
#include "Quaternion.h"

namespace D3DEngine
{
	Transform::Transform()
	{
		//Init Parent Matrix
		m_ParentMatrix = Matrix4f();

		std::cerr << "I AM CREATED" << std::endl;
	}

	Transform::~Transform()
	{
		//Empty
	}

	Matrix4f Transform::GetTransformation() 
	{
		Matrix4f Translation = Translation.InitTranslation(m_Position.GetX(), m_Position.GetY(), m_Position.GetZ());
		Matrix4f Rotation = *m_Rotation.ToRotationMatrix();
		Matrix4f ScaleMatrix = ScaleMatrix.InitScaling(m_Scaling.GetX(), m_Scaling.GetY(), m_Scaling.GetZ());

		//Apply Rotation First
		return GetParentMatrix()->Mult((Translation.Mult(Rotation.Mult(ScaleMatrix))));
	}
	bool Transform::HasChanged()
	{
		if (m_Parent != nullptr)
		{
			bool parentHasChanged = m_Parent->HasChanged();
			if (parentHasChanged) 
				return true;
		}

		if (FirstTime)
		{	
			m_PrevPosition.Set(m_Position);
			m_PrevRotation.Set(m_Rotation);
			m_PrevScaling.Set(m_Scaling);
			FirstTime = false;
			return true;
		}
		
		if (m_Position != m_PrevPosition)
			return true;
		if (m_Rotation != m_PrevRotation)
			return true;
		if (m_Scaling != m_PrevScaling)
			return true;

		return false;
	}

	Vector3f Transform::GetTransformedPos()
	{
		return GetParentMatrix()->Transform(m_Position);
	}

	void Transform::Rotate(Vector3f Axis, float Angle)
	{
		m_Rotation = Quaternion(Axis, Angle).Mult(m_Rotation).Normalise();
	}
	
	void Transform::Update()
	{
		if (FirstTime)
		{
			m_PrevPosition = Vector3f();
			m_PrevRotation = Quaternion();
			m_PrevScaling = Vector3f();
		}
		else
		{
			m_PrevPosition = m_PrevPosition + Vector3f(1, 1, 1);
			m_PrevRotation.SetX(m_Rotation.GetX() + 120);
			m_PrevScaling = m_Scaling * 12;
			FirstTime = false;
		}
	}

	Quaternion Transform::GetTransformedRot()
	{
		Quaternion parentRotation = Quaternion(0,0,0,1);

		if (m_Parent != nullptr)
			parentRotation = m_Parent->GetTransformedRot();

		return parentRotation.Mult(m_Rotation);
	}

	Matrix4f* Transform::GetParentMatrix()
	{
		if ((m_Parent != nullptr) && (m_Parent->HasChanged()))
		{
			m_ParentMatrix = m_Parent->GetTransformation();

			m_PrevPosition.Set(m_Position);
			m_PrevRotation.Set(m_Rotation);
			m_PrevScaling.Set(m_Scaling);
		}
		return &m_ParentMatrix;
	}


	Transform::Transform(const Transform &other) 
	{
		std::cerr << "Copied" << std::endl;
		m_Position = other.m_Position;
		m_Rotation = other.m_Rotation;
		m_Scaling = other.m_Scaling;

		FirstTime = other.FirstTime;

		m_PrevPosition = other.m_PrevPosition;
		m_PrevRotation = other.m_PrevRotation;
		m_PrevScaling = other.m_PrevScaling;

		m_Parent = other.m_Parent;
		m_ParentMatrix = other.m_ParentMatrix;
		FirstTime = other.FirstTime;
	}

	Transform& Transform::operator=(const Transform &other)
	{
		m_Position = other.m_Position;
		m_Rotation = other.m_Rotation;
		m_Scaling = other.m_Scaling;

		FirstTime = other.FirstTime;

		m_PrevPosition = other.m_PrevPosition;
		m_PrevRotation = other.m_PrevRotation;
		m_PrevScaling = other.m_PrevScaling;

		m_Parent = other.m_Parent;
		m_ParentMatrix = other.m_ParentMatrix;
		FirstTime = other.FirstTime;

		return *this;
	}
}