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
		inline PointLight GetActivePointLight() { return m_ActivePointLight; }
		inline SpotLight GetSpotLight() { return m_SpotLight; }
		//Add Lights
		inline void AddDirectionalLight(DirectionalLight* directionalLight) { m_DirectionalLights.push_back(directionalLight); }
		inline void AddPointLight(PointLight* pointLight) { m_PointLights.push_back(pointLight); }

		void ClearLightList();


	private:
		Shader* m_ShaderForwardAmbient;
		Shader* m_ShaderForwardDirectional;
		Shader* m_ShaderPointLight;
		Shader* m_ShaderSpotLight;

		Camera* m_Camera;

		Vector3f m_AmbientLight;
		DirectionalLight m_ActiveDirectionalLight;
		PointLight m_ActivePointLight;
		SpotLight m_SpotLight;

		//Permanent Structures
		std::vector<DirectionalLight*> m_DirectionalLights = std::vector<DirectionalLight*>();
		std::vector<PointLight*> m_PointLights = std::vector<PointLight*>();
		//std::vector<DirectionalLight*> m_DirectionalLights = std::vector<DirectionalLight*>();
	};
}