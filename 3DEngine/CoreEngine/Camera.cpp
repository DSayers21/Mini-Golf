//Includes
#include "Camera.h"
#include "RenderEngine.h"
#include "MainComp.h"

namespace D3DEngine
{
	Camera::Camera(float FOV, float AspectRatio, float zNear, float zFar)
	{
		//Display Message
		std::cerr << "Mouse Created" << std::endl;
		//Default Camera Perspective
		m_Projection = Matrix4f().InitPerspective(FOV, AspectRatio, zNear, zFar);
	}

	Matrix4f Camera::GetViewProjection()
	{
		//Get the rotation matrix
		Matrix4f CameraRotMat = GetTransform()->GetTransformedRot().Conjugate().ToRotationMatrix();
		//Get the camera position
		Vector3f CameraPos = GetTransform()->GetTransformedPos() * (-1);
		//Get the translation matrix
		Matrix4f CameraTransMat = Matrix4f().InitTranslation(
			CameraPos.GetX(),
			CameraPos.GetY(),
			CameraPos.GetZ()
		);
		//Return the projection multiplied by the camerarotation and the transformation
		return m_Projection.Mult(CameraRotMat.Mult(CameraTransMat));
	}

	void Camera::AddToEngine(MainComp * mainComp)
	{
		//Add the camera to the rendering engine
		mainComp->GetRenderEngine()->AddCamera(this);
	}
}