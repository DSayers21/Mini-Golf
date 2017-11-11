#pragma once

#include "GameObject.h"
#include "BasicShader.h"
#include "MathBasics.h"
#include "Camera.h"

#include "Input.h"
#include "Time.h"

namespace D3DEngine
{
	class RenderEngine
	{
	public:
		RenderEngine();
		~RenderEngine();

		void Render(GameObject* Object);

		inline void SetCamera(Camera* camera) { m_Camera = camera; }
		inline Camera* GetCamera() { return m_Camera; }

		//Temp
		void CameraInput(Input& input, Time& time);

	private:
		BasicShader* BShade;
		Camera* m_Camera;
	};
}