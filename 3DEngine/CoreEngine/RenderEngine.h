#pragma once

#include "GameObject.h"

#include "Shader.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "MathBasics.h"
#include "Camera.h"
#include "Vector3f.h"

#include "Input.h"
#include "Time.h"

#include <vector>

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
		inline DirectionalLight GetActiveDirectionalLight() { return m_ActiveDirectionalLight; }
		inline PointLight GetPointLight() { return m_PointLight; }
		inline SpotLight GetSpotLight() { return m_SpotLight; }
		//Add Lights
		inline void AddDirectionalLight(DirectionalLight* directionalLight) { m_DirectionalLights.push_back(directionalLight); }

		inline void ClearLightList() { m_DirectionalLights.clear(); }


	private:
		Shader* m_ShaderForwardAmbient;
		Shader* m_ShaderForwardDirectional;
		Shader* m_ShaderPointLight;
		Shader* m_ShaderSpotLight;

		Camera* m_Camera;

		Vector3f m_AmbientLight;
		DirectionalLight m_ActiveDirectionalLight;
		DirectionalLight m_DirectionalLight2;
		PointLight m_PointLight;
		SpotLight m_SpotLight;

		//Permanent Structures
		std::vector<DirectionalLight*> m_DirectionalLights = std::vector<DirectionalLight*>();
	};
}