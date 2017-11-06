#include "Transform.h"

namespace D3DEngine
{
	Transform::Transform()
	{
	}

	Transform::~Transform()
	{
	}

	Matrix4f Transform::GetTransformation()
	{
		Vector3f Temp = m_Rotation;
		Matrix4f Translation = Translation.InitTranslation(m_Translation.GetX(), m_Translation.GetY(), m_Translation.GetZ());
		Matrix4f Rotation = Rotation.InitRotation(m_Rotation.GetX(), m_Rotation.GetY(), m_Rotation.GetZ());
		Matrix4f ScaleMatrix = ScaleMatrix.InitScaling(m_Scaling.GetX(), m_Scaling.GetY(), m_Scaling.GetZ());

		//Apply Rotation First
		Matrix4f Res;
		Res.InitIdentity();
		return (Translation.Mult(Rotation.Mult(ScaleMatrix)));
	}

	Matrix4f Transform::GetProjectedTransformation()
	{
		Matrix4f TransMat = GetTransformation();
		Matrix4f ProjMat;
		Matrix4f CameraRotMat;
		Matrix4f CameraTransMat;

		ProjMat.InitProjection(Transform::m_FOV, Transform::m_Width, Transform::m_Height, Transform::m_zNear, Transform::m_zFar);
		CameraRotMat.InitCamera(m_Camera->GetForward(), m_Camera->GetUp());
		CameraTransMat.InitTranslation(-m_Camera->GetPos().GetX(), -m_Camera->GetPos().GetY(), -m_Camera->GetPos().GetZ());



		return ProjMat.Mult(CameraRotMat.Mult(CameraTransMat.Mult(TransMat)));
	}

	void Transform::SetProjection(float FOV, float Width, float Height, float zNear, float zFar)
	{
		Transform::m_FOV = FOV;
		Transform::m_Width = Width;
		Transform::m_Height = Height;
		Transform::m_zNear = zNear;
		Transform::m_zFar = zFar;
	}
}