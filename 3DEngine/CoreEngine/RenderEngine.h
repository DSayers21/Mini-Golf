#pragma once

#include "GameObject.h"

#include "Shader.h"

#include "BaseLight.h"
#include "Camera.h"
#include "Window.h"

#include "MathBasics.h"
#include "Camera.h"
#include "Vector3f.h"

#include "ResourceManagement/MappedValues.h"
#include "ResourceManagement/ShaderList.h"

#include "Input.h"
#include "Time.h"

#include <vector>
#include <map>
#include <thread>

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

		int GetSamplerSlot(const std::string& SamplerName);

		void UpdateUniformStruct(Transform* transform, Material* material, Shader* shader, std::string& UniformName, std::string& UniformType);

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline BaseLight* GetActiveLight() { return ActiveLight; }
		inline ShaderList* GetShaderList() { return m_ShaderList; }
		//inline SDL_Renderer* GetSDLRenderer() { return m_Renderer; }
		//Add Lights
		inline void AddLight(BaseLight* Light) { m_Lights.push_back(Light); }
		inline void AddCamera(Camera* camera) { m_Camera = camera; }

		inline void SetActiveLight(BaseLight* Light) { ActiveLight = Light; }

		void ResetEngine();

	private: 
		//SDL_Renderer* m_Renderer = NULL;
		Shader* m_ShaderForwardAmbient;

		Camera* m_Camera;

		Vector3f m_AmbientLight;

		ShaderList* m_ShaderList;

		//Permanent Structures
		std::vector<BaseLight*> m_Lights = std::vector<BaseLight*>();
		BaseLight* ActiveLight;

		std::map<std::string, int> SamplerMap;
	};
}