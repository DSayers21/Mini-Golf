#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "DirectionalLight.h"
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

		void InitGraphics();

		void SetTextures(bool Enabled);

		void ClearScreen();

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline DirectionalLight GetDirectionalLight() { return m_DirectionalLight; }
	private:
		Shader* m_ShaderForwardAmbient;
		Shader* m_ShaderForwardDirectional;
		Camera* m_Camera;
		Vector3f m_AmbientLight;
		DirectionalLight m_DirectionalLight;
		DirectionalLight m_DirectionalLight2;
	};
}