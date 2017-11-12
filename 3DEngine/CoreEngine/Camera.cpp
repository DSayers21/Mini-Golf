#include "Camera.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	Camera::Camera(float FOV, float AspectRatio, float zNear, float zFar)
	{
		//Default Camera

		//GetTransform()->GetPosition()->Set(0, 0, 0);
		//GetTransform()->GetRotation()->GetForward().Set(0, 0, 1);
		//GetTransform()->GetRotation()->GetUp().Set(0, 1, 0);

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

	void Camera::Input(float Delta)
	{
		float MoveAmount = 4 * Delta;
		float RotAmount = 32 * Delta;

		/*if (input.GetKey(KEY_W))
			Move(GetTransform()->GetRotation()->GetForward(), MoveAmount);
		if (input.GetKey(KEY_S))
			Move(GetTransform()->GetRotation()->GetForward(), -MoveAmount);
		if (input.GetKey(KEY_A))
			Move(GetTransform()->GetRotation()->GetLeft(), MoveAmount);
		if (input.GetKey(KEY_D))
			Move(GetTransform()->GetRotation()->GetRight(), MoveAmount);*/

		//GetTransform()->GetRotation()->Mult(Quaternion());
		//if (input.GetKey(KEY_UP))
		//	RotateY(-RotAmount);
		//if (input.GetKey(KEY_DOWN))
		//	RotateY(RotAmount);
		//if (input.GetKey(KEY_LEFT))
		//	RotateX(-RotAmount);
		//if (input.GetKey(KEY_RIGHT))
		//	RotateX(RotAmount);
	}

	void Camera::Move(Vector3f Direction, float Amount)
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition()->Add(Vector3f(Direction * Amount)));
		/*Vector3f Test = (Direction * Amount);
		Vector3f Test2 = m_Pos + Test;
		m_Pos.SetX(Test2.GetX());
		m_Pos.SetY(Test2.GetY());
		m_Pos.SetZ(Test2.GetZ());*/
	}

	//void Camera::RotateX(float Angle)
	//{
	//	Angle = TO_RADIANS(Angle);
	//	//Horizontal Axis
	//	Vector3f HAxis = yAxi.CrossProduct(m_Forward);
	//	HAxis.Normalise();

	//	m_Forward.Rotate(yAxi, Angle);
	//	m_Forward.Normalise();

	//	m_Up = m_Forward.CrossProduct(HAxis);
	//	m_Up.Normalise();
	//}

	//void Camera::RotateY(float Angle)
	//{
	//	Angle = TO_RADIANS(Angle);
	//	//Horizontal Axis
	//	Vector3f HAxis = yAxi.CrossProduct(m_Forward);
	//	HAxis.Normalise();

	//	m_Forward.Rotate(HAxis, Angle);
	//	m_Forward.Normalise();

	//	m_Up = m_Forward.CrossProduct(HAxis);
	//	m_Up.Normalise();
	//}

	//Vector3f Camera::GetLeft()
	//{
	//	Vector3f Left = m_Forward.CrossProduct(m_Up);
	//	Left.Normalise();
	//	return Left;
	//}

	//Vector3f Camera::GetRight()
	//{
	//	Vector3f Right = m_Up.CrossProduct(m_Forward);
	//	Right.Normalise();
	//	return Right;
	//}
}