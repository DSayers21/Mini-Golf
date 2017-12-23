#pragma once

//Includes
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

namespace D3DEngine
{	
	//Struct of the text to be rendered
	struct TextToRender
	{
		TextToRender(std::string Text, Vector3f Colour, int x, int y)
		{
			m_Text = Text;		//Set the text
			m_Colour = Colour;	//Set the colour
			X = x;				//Set the X position
			Y = y;				//Set the Y position
		}

		std::string m_Text; //Text to be rendered
		Vector3f m_Colour;	//Colour of the text
		int X, Y;			//Position of the text
	};

	//Forward Declarations
	class TextRendering;

	//Inherits from Mapped Values
	class RenderEngine : public MappedValues
	{
	public:
		//Constructor
		RenderEngine(Window* Window);
		//Destructor
		~RenderEngine();
		//Render the current scene
		void Render(GameObject* Object);
		//Render all the UI text
		void RenderText();
		//Init the graphics
		void InitGraphics();
		//Set the textures
		void SetTextures(bool Enabled);
		//Clear the screen
		void ClearScreen();
		//Get the sampler slot
		int GetSamplerSlot(const std::string& SamplerName);
		//Update the uniforms struct
		void UpdateUniformStruct(Transform* transform, Material* material, Shader* shader, std::string& UniformName, std::string& UniformType);

		//Getters
		inline Camera* GetCamera() { return m_Camera; }
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline BaseLight* GetActiveLight() { return m_ActiveLight; }
		inline ShaderList* GetShaderList() { return m_ShaderList; }
		inline Window* GetWindow() { return m_Window; }

		//Add Light
		inline void AddLight(BaseLight* Light) { m_Lights.push_back(Light); }
		//Add Text
		void AddText(const std::string& Name, TextToRender Content);
		//Remove Text
		void RemoveText(const std::string& Name);
		//Remove all Text
		void RemoveAllText();
		//Add the camera
		inline void AddCamera(Camera* camera) { m_Camera = camera; }
		//Set the active light
		inline void SetActiveLight(BaseLight* Light) { m_ActiveLight = Light; }
		//Reset the engine back to base
		void ResetEngine();

	private: 
		//Pointer to the window
		Window* m_Window;
		//Ambient light shader
		Shader* m_ShaderForwardAmbient;
		//Pointer to the camera
		Camera* m_Camera;
		//Ambient Light value
		Vector3f m_AmbientLight;
		//List of all shaders
		ShaderList* m_ShaderList;
		//Pointer to the text renderer
		TextRendering* m_TextRender;

		//Map of all text that needs to be rendered
		std::map<std::string, TextToRender> m_Text = std::map<std::string, TextToRender>();
		//List of all lights that need to be processed
		std::vector<BaseLight*> m_Lights = std::vector<BaseLight*>();
		//Pointer to the active light
		BaseLight* m_ActiveLight;
		//Sampler map
		std::map<std::string, int> m_SamplerMap;
	};
}