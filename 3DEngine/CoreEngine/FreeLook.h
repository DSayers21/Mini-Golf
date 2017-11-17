#pragma once

#include "GameComponent.h"

namespace D3DEngine
{
	class FreeLook : public GameComponent
	{
	public:
		FreeLook();
		~FreeLook();
		void Input(GetInput * input, float Delta);
		void Move(Vector3f Direction, float Amount);

	private:
		bool m_MouseControl = false; //Move Camera With Mouse

		Vector3f yAxi = Vector3f(0, 1, 0);
	};
}