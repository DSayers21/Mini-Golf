#include "Camera.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	Camera::Camera(float FOV, float AspectRatio, float zNear, float zFar)
	{
		//Default Camera
		m_Projection = Matrix4f().InitPerspective(FOV, AspectRatio, zNear, zFar);
	}

	Matrix4f Camera::GetViewProjection()
	{
		Matrix4f CameraRotMat = *GetTransform()->GetRotation()->ToRotationMatrix();
		Matrix4f CameraTransMat = Matrix4f().InitTranslation(
			-GetTransform()->GetPosition()->GetX(),
			-GetTransform()->GetPosition()->GetY(), 
			-GetTransform()->GetPosition()->GetZ()
		);

		return m_Projection.Mult(CameraRotMat.Mult(CameraTransMat));
	}

	void Camera::AddToRenderingEngine(RenderEngine * renderEngine)
	{
		renderEngine->AddCamera(this);
	}

	void Camera::Input(GetInput* input, float Delta)
	{
		float MoveAmount = 4 * Delta;
		float RotAmount = 32 * Delta;

		if (input->GetKey(KEY_W))
			Move(GetTransform()->GetRotation()->GetForward(), MoveAmount);
		if (input->GetKey(KEY_S))
			Move(GetTransform()->GetRotation()->GetForward(), -MoveAmount);
		if (input->GetKey(KEY_A))
			Move(GetTransform()->GetRotation()->GetLeft(), MoveAmount);
		if (input->GetKey(KEY_D))
			Move(GetTransform()->GetRotation()->GetRight(), MoveAmount);


		if (input->GetKey(KEY_UP))
			RotateY(-RotAmount);
		if (input->GetKey(KEY_DOWN))
			RotateY(RotAmount);
		if (input->GetKey(KEY_LEFT))
			RotateX(-RotAmount);
		if (input->GetKey(KEY_RIGHT))
			RotateX(RotAmount);
	}

	void Camera::Move(Vector3f Direction, float Amount)
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition()->Add(Vector3f(Direction * Amount)));
	}

	void Camera::RotateX(float Angle)
	{
		Angle = TO_RADIANS(Angle);
		//Horizontal Axis
		Vector3f HAxis = yAxi.CrossProduct(GetTransform()->GetRotation()->GetForward());
		HAxis.Normalise();

		GetTransform()->GetRotation()->GetForward().Rotate(yAxi, Angle);
		GetTransform()->GetRotation()->GetForward().Normalise();

		GetTransform()->GetRotation()->GetUp() = GetTransform()->GetRotation()->GetForward().CrossProduct(HAxis);
		GetTransform()->GetRotation()->GetUp().Normalise();
	}

	void Camera::RotateY(float Angle)
	{
		Angle = TO_RADIANS(Angle);
		//Horizontal Axis
		Vector3f HAxis = yAxi.CrossProduct(GetTransform()->GetRotation()->GetForward());
		HAxis.Normalise();

		GetTransform()->GetRotation()->GetForward().Rotate(HAxis, Angle);
		GetTransform()->GetRotation()->GetForward().Normalise();

		GetTransform()->GetRotation()->GetUp() = GetTransform()->GetRotation()->GetForward().CrossProduct(HAxis);
		GetTransform()->GetRotation()->GetUp().Normalise();
	}
}