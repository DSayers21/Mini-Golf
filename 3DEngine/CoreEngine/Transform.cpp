#include "Transform.h"
#include <iostream>

namespace D3DEngine
{
	Transform::Transform()
	{
		//Init Parent Matrix
		m_ParentMatrix = Matrix4f();
		//m_ParentMatrix->InitIdentity();

		m_PrevPosition = m_Position + 1;
		m_PrevRotation = m_Rotation.Mult(Quaternion(1, 0, 3, 0));
		m_PrevScaling = m_Scaling * 2;

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

		//Only Get parent transformation if parent exists and has changed
		if (m_Parent != nullptr)
		{
			bool changed = m_Parent->HasChanged();
			//changed = true;
			if (changed)
			{
				m_ParentMatrix = m_Parent->GetTransformation();

				m_PrevPosition.Set(m_Position);
				m_PrevRotation.Set(m_Rotation);
				m_PrevScaling.Set(m_Scaling);
			}
		}
		//Apply Rotation First
		return m_ParentMatrix.Mult((Translation.Mult(Rotation.Mult(ScaleMatrix))));
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