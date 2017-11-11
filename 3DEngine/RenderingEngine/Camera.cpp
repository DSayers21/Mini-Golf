#include "Camera.h"

namespace D3DEngine
{
	Camera::Camera()
	{
		//Default Camera
		*this = Camera(Vector3f(0, 0, 0), Vector3f(0, 0, 1), Vector3f(0, 1, 0));

	}

	Camera::Camera(Vector3f Pos, Vector3f Forward, Vector3f Up)
	{
		m_Pos = Pos;
		m_Forward = Forward;
		m_Up = Up;

		m_Up.Normalise();
		m_Forward.Normalise();
	}

	void Camera::DoInput(Input& input, Time& time)
	{
		float MoveAmount = 0.001;
		float RotAmount = 0.01;

		if (input.GetKey(KEY_W))
			Move(GetForward(), MoveAmount);
		if (input.GetKey(KEY_S))
			Move(GetForward(), -MoveAmount);
		if (input.GetKey(KEY_A))
			Move(GetLeft(), MoveAmount);
		if (input.GetKey(KEY_D))
			Move(GetRight(), MoveAmount);

		if (input.GetKey(KEY_UP))
			RotateY(-RotAmount);
		if (input.GetKey(KEY_DOWN))
			RotateY(RotAmount);
		if (input.GetKey(KEY_LEFT))
			RotateX(-RotAmount);
		if (input.GetKey(KEY_RIGHT))
			RotateX(RotAmount);
	}

	void Camera::Move(Vector3f Direction, float Amount)
	{
		Vector3f Test = (Direction * Amount);
		Vector3f Test2 = m_Pos + Test;
		m_Pos.SetX(Test2.GetX());
		m_Pos.SetY(Test2.GetY());
		m_Pos.SetZ(Test2.GetZ());
	}

	void Camera::RotateX(float Angle)
	{
		//Horizontal Axis
		Vector3f HAxis = yAxi.CrossProduct(m_Forward);
		HAxis.Normalise();

		m_Forward.Rotate(Angle, yAxi);
		m_Forward.Normalise();

		m_Up = m_Forward.CrossProduct(HAxis);
		m_Up.Normalise();
	}

	void Camera::RotateY(float Angle)
	{
		//Horizontal Axis
		Vector3f HAxis = yAxi.CrossProduct(m_Forward);
		HAxis.Normalise();

		m_Forward.Rotate(Angle, HAxis);
		m_Forward.Normalise();

		m_Up = m_Forward.CrossProduct(HAxis);
		m_Up.Normalise();
	}

	Vector3f Camera::GetLeft()
	{
		Vector3f Left = m_Forward.CrossProduct(m_Up);
		Left.Normalise();
		return Left;
	}

	Vector3f Camera::GetRight()
	{
		Vector3f Right = m_Up.CrossProduct(m_Forward);
		Right.Normalise();
		return Right;
	}
}