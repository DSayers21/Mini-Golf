#include "Transform.h"

namespace D3DEngine
{
	Transform::Transform()
	{
		//Empty
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
		Matrix4f Res;
		Res.InitIdentity();
		return (Translation.Mult(Rotation.Mult(ScaleMatrix)));
	}
}