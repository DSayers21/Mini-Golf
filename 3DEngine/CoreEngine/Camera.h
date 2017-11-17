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
		
		void AddToEngine(MainComp * mainComp);

	private:
		Matrix4f m_Projection;
	};
}