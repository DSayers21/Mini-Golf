//Includes
#include "FreeLook.h"

namespace D3DEngine
{
	FreeLook::FreeLook()
	{
		//Set moust control to false
		m_MouseControl = false;
	}


	FreeLook::~FreeLook()
	{
		//Display message
		std::cerr << "Destructor: Free Look Component" << std::endl;
	}

	void FreeLook::Input(GetInput* input, float Delta)
	{
		//Get the move amount modified by the delta
		float MoveAmount = 4 * Delta;
		//Get the rotation amount modified by the delta
		float RotAmount = 0.5 * Delta;

		//Move Mouse Handles
		if (input->GetKey(KEY_W))	//Is W key pressed
			Move(GetTransform()->GetRotation()->GetForward(), MoveAmount);	//Move appropriately
		if (input->GetKey(KEY_S))	//Is S key pressed
			Move(GetTransform()->GetRotation()->GetForward(), -MoveAmount);	//Move appropriately
		if (input->GetKey(KEY_A))	//Is A key pressed
			Move(GetTransform()->GetRotation()->GetLeft(), MoveAmount);		//Move appropriately
		if (input->GetKey(KEY_D))	//Is D key pressed
			Move(GetTransform()->GetRotation()->GetRight(), MoveAmount);	//Move appropriately
			
		//Rotation Mouse Handles
		if (input->GetMouseUp(MOUSE_LEFT_BUTTON))
		{
			//Set mouse control to false
			m_MouseControl = false;
			//Set the cursor to true
			input->SetCursor(true);
		}
		if (input->GetMouseDown(MOUSE_LEFT_BUTTON))
		{
			//Set mouse control to true
			m_MouseControl = true;
			//Set the mouse position to the center of the screen
			input->SetMousePosition(input->GetWindow()->GetCenter());
			//Set the cursor to false (cursor wont be rendered)
			input->SetCursor(false);
		}
		//Camera Rotation
		if (m_MouseControl)
		{
			//Set the sensitivity
			float Sensitivity = .5f;
			//Get the different between the mouse and the center of the screen
			Vector2f DeltaPos = input->GetMousePos() - input->GetWindow()->GetCenter();

			//Test if the mouse is at the center of the screen
			bool rotY = (DeltaPos.GetX() == 0) ? false : true;
			bool rotX = (DeltaPos.GetY() == 0) ? false : true;

			//Rotate on the Y plane
			if (rotY)
				GetTransform()->Rotate(yAxi, TO_RADIANS(DeltaPos.GetX() * Sensitivity));
			//Rotate on the X plane
			if (rotX)
				GetTransform()->Rotate(GetTransform()->GetRotation()->GetRight(), TO_RADIANS(DeltaPos.GetY(), *Sensitivity));
			//Set mouse position to the centre of the screen
			if (rotY || rotX)
				input->SetMousePosition(input->GetWindow()->GetCenter());
		}
	}

	void FreeLook::Move(Vector3f Direction, float Amount)
	{
		//Set the position to the passeed in value
		GetTransform()->SetPosition(GetTransform()->GetPosition()->Add(Vector3f(Direction * Amount)));
	}
}