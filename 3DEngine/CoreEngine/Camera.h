#pragma once

//Includes
#include "Vector3f.h"
#include <iostream>
#include <string>
#include "Matrix4f.h"
#include "MathBasics.h"
#include "GameComponent.h"

namespace D3DEngine
{
	//Inherits from Game Component
	class Camera : public GameComponent
	{
	public:
		//Constructor
		Camera(float FOV, float AspectRatio, float zNear, float zFar);
		//Empty Destructor
		~Camera() {}
		//Function to return the view projection
		Matrix4f GetViewProjection();
		//Function to add the camera to the rendering engine
		void AddToEngine(MainComp * mainComp);

	private:
		//Matrix representing the 3D projection
		Matrix4f m_Projection;
	};
}