#include "Camera.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	Camera::Camera(float FOV, float AspectRatio, float zNear, float zFar)
	{
		//Default Camera
		m_Projection = Matrix4f().InitPerspective(FOV, AspectRatio, zNear, zFar);
		m_MouseControl = false;

		std::cerr << "Mouse Created" << std::endl;
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
		float RotAmount = 0.5 * Delta;

		//Move Mouse Handles
		if (input->GetKey(KEY_W))
			Move(GetTransform()->GetRotation()->GetForward(), MoveAmount);
		if (input->GetKey(KEY_S))
			Move(GetTransform()->GetRotation()->GetForward(), -MoveAmount);
		if (input->GetKey(KEY_A))
			Move(GetTransform()->GetRotation()->GetLeft(), MoveAmount);
		if (input->GetKey(KEY_D))
			Move(GetTransform()->GetRotation()->GetRight(), MoveAmount);

		//Rotation Mouse Handles
		if (input->GetMouseUp(MOUSE_LEFT_BUTTON))
		{
			m_MouseControl = false;
			input->SetCursor(true);
		}
		if (input->GetMouseDown(MOUSE_LEFT_BUTTON))
		{
			m_MouseControl = true;
			input->SetMousePosition(Vector2f(800 / 2, 600 / 2));
			input->SetCursor(false);
		}
		//Camera Rotation
		if (m_MouseControl)
		{
			float Sensitivity = -.5f;
			Vector2f DeltaPos = input->GetMousePos();
			DeltaPos.SetX(DeltaPos.GetX() - 400);
			DeltaPos.SetY(DeltaPos.GetY() - 300);

			bool rotY = (DeltaPos.GetX() == 0) ? false : true;
			bool rotX = (DeltaPos.GetY() == 0) ? false : true;

			if (rotY)
				GetTransform()->SetRotation(&GetTransform()->GetRotation()->Mult(*Quaternion().InitRotation(yAxi, TO_RADIANS(DeltaPos.GetX() * Sensitivity))).Normalise());

			if (rotX)
				GetTransform()->SetRotation(&GetTransform()->GetRotation()->Mult(*Quaternion().InitRotation(GetTransform()->GetRotation()->GetRight(), TO_RADIANS(-DeltaPos.GetY(), * Sensitivity))).Normalise());

			if (rotY || rotX)
				input->SetMousePosition(Vector2f(800 / 2, 600 / 2));
		}
	}

	void Camera::Move(Vector3f Direction, float Amount)
	{
		GetTransform()->SetPosition(GetTransform()->GetPosition()->Add(Vector3f(Direction * Amount)));
	}
}