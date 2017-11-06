#pragma once

#include "Vector3f.h"
#include "Time.h"
#include "Input.h"
#include <iostream>
#include <string>

namespace D3DEngine
{
	class Camera
	{
	public:
		Camera();
		Camera(Vector3f Pos, Vector3f Forward, Vector3f Up);

		void DoInput(Input& input, Time& time);

		void Move(Vector3f Direction, float Amount);
		void RotateX(float Angle);
		void RotateY(float Angle);

		//Getters
		Vector3f GetPos() { return m_Pos; }
		Vector3f GetForward() { return m_Forward; }
		Vector3f GetUp() {return m_Up; }
		Vector3f GetLeft();	//Gets normalised vector facing left
		Vector3f GetRight();	//Gets normalised vector facing right

		//Setters
		void SetPos(Vector3f Pos) { m_Pos = Pos; }
		void SetForward(Vector3f Forward) { m_Forward = Forward; }
		void SetUp(Vector3f Up) { m_Up = Up; }

	private:
		Vector3f m_Pos;
		//Represents which direction is up and forward
		Vector3f m_Forward;
		Vector3f m_Up;
		//
	    Vector3f yAxi = Vector3f(0,1,0);
	};
}