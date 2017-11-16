#pragma once

#include "GameObject.h"

#include "Shader.h"
#include "ForwardAmbient.h"

#include "BaseLight.h"
#include "Camera.h"

#include "MathBasics.h"
#include "Camera.h"
#include "Vector3f.h"

#include "ResourceManagement/MappedValues.h"

#include "Input.h"
#include "Time.h"

#include <vector>
#include <map>

namespace D3DEngine
{
	class RenderEngine : public MappedValues
	{
	public:
		RenderEngine();
		~RenderEngine();

		void Render(GameObject* Object);

		//inline void SetCamera(Camera* camera) { m_Camera = camera; }
		inline Camera* GetCamera() { return m_Camera; }

		void InitGraphics();

		void SetTextures(bool Enabled);

		void ClearScreen();

		int GetSamplerSlot(std::string SamplerName);

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline BaseLight* GetActiveLight() { return ActiveLight; }
		//Add Lights
		inline void AddLight(BaseLight* Light) { m_Lights.push_back(Light); }
		inline void AddCamera(Camera* camera) { m_Camera = camera; }

	private:
		Shader* m_ShaderForwardAmbient;

		Camera* m_Camera;

		Vector3f m_AmbientLight;

		//Permanent Structures
		std::vector<BaseLight*> m_Lights = std::vector<BaseLight*>();
		BaseLight* ActiveLight;

		std::map<std::string, int> SamplerMap;
	};
}