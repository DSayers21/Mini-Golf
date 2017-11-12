#pragma once

#include "Vector3f.h"
#include "Time.h"
#include "Input.h"
#include <iostream>
#include <string>
#include "Matrix4f.h"
#include "MathBasics.h"

namespace D3DEngine
{
	class Camera
	{
	public:
		Camera(float FOV, float AspectRatio, float zNear, float zFar);

		Matrix4f GetViewProjection();

		void DoInput(Input& input, float Delta);

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
		bool m_MouseControl = false; //Move Camera With Mouse

		Vector3f m_Pos;
		//Represents which direction is up and forward
		Vector3f m_Forward;
		Vector3f m_Up;
		//
	    Vector3f yAxi = Vector3f(0,1,0);

		Matrix4f m_Projection;
	};
}