#include "Camera.h"
#include "RenderEngine.h"
#include "MainComp.h"

namespace D3DEngine
{
	Camera::Camera(float FOV, float AspectRatio, float zNear, float zFar)
	{
		//Default Camera
		m_Projection = Matrix4f().InitPerspective(FOV, AspectRatio, zNear, zFar);

		std::cerr << "Mouse Created" << std::endl;
	}

	Matrix4f Camera::GetViewProjection()
	{
		Matrix4f CameraRotMat = *GetTransform()->GetTransformedRot().Conjugate().ToRotationMatrix();
		Vector3f CameraPos = GetTransform()->GetTransformedPos() * (-1);
		Matrix4f CameraTransMat = Matrix4f().InitTranslation(
			CameraPos.GetX(),
			CameraPos.GetY(),
			CameraPos.GetZ()
		);

		return m_Projection.Mult(CameraRotMat.Mult(CameraTransMat));
	}

	void Camera::AddToEngine(MainComp * mainComp)
	{
		mainComp->GetRenderEngine()->AddCamera(this);
	}
}