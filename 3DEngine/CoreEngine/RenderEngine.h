#pragma once

#include "GameObject.h"
#include "ForwardAmbient.h"
#include "MathBasics.h"
#include "Camera.h"
#include "Vector3f.h"

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
		void CameraInput(Input& input, float Delta);

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }

	private:
		ForwardAmbient* m_ShaderForwardAmbient;
		Camera* m_Camera;
		Vector3f m_AmbientLight;
	};
}