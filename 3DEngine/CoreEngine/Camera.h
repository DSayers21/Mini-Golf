#pragma once

#include "Vector3f.h"
#include "Time.h"
#include <iostream>
#include <string>
#include "Matrix4f.h"
#include "MathBasics.h"
#include "GameComponent.h"

namespace D3DEngine
{
	class Camera : public GameComponent
	{
	public:
		Camera(float FOV, float AspectRatio, float zNear, float zFar);

		Matrix4f GetViewProjection();
		
		void Move(Vector3f Direction, float Amount);
		void RotateX(float Angle);
		void RotateY(float Angle);

		void AddToRenderingEngine(RenderEngine * renderEngine);
		void Input(GetInput* input, float Delta);

	private:
		bool m_MouseControl = false; //Move Camera With Mouse

	    Vector3f yAxi = Vector3f(0,1,0);
		
		Matrix4f m_Projection;
	};
}