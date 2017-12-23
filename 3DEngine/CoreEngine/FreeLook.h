#pragma once

//Includes
#include "GameComponent.h"

namespace D3DEngine
{
	//Inherit from GameComponent
	class FreeLook : public GameComponent
	{
	public:
		//Constructor
		FreeLook();
		//Destructor
		~FreeLook();
		//Input handeling function
		void Input(GetInput * input, float Delta);
		//Move Functions
		void Move(Vector3f Direction, float Amount);

	private:
		bool m_MouseControl = false; //Move Camera With Mouse
		//The YAxis
		Vector3f yAxi = Vector3f(0, 1, 0);
	};
}