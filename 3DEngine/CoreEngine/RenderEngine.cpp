#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		MappedValues();
		InitGraphics();

		m_ShaderList = new ShaderList();
		//Ambient Light
		m_ShaderForwardAmbient = new Shader("Forward-Ambient", m_ShaderList);
		//Setup Lighting
		m_AmbientLight = new Vector3f(1.0f, 1.0f, 1.0f);

		AddVector3f("ambient", *m_AmbientLight);

		SamplerMap = std::map<std::string, int>();
		SamplerMap.insert(std::pair<std::string, int>("Diffuse", 0));
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render(GameObject * Object)
	{
		ClearScreen();

		Object->Draw(m_ShaderForwardAmbient, this);

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE); //Existing colour times one, plus other colour times one
		glDepthMask(false);			 //Disbale writing to the depth buffer
		glDepthFunc(GL_EQUAL);		 //Only change the pixel, if it has the exact same depth value
		//Any Code here will be blended into the image

		//Draw All Lights
		for (int i = 0; i < m_Lights.size(); i++)
		{
			ActiveLight = m_Lights[i];
			Object->Draw(ActiveLight->GetShader(), this);
		}

		//end of blending
		glDepthFunc(GL_LESS);
		glDepthMask(true);			 //Enable writing to the depth buffer
		glDisable(GL_BLEND);
	}

	void RenderEngine::InitGraphics()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		SetTextures(true);
		glEnable(GL_DEPTH_CLAMP);
	}

	void RenderEngine::SetTextures(bool Enabled)
	{
		(Enabled) ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	}

	void RenderEngine::ClearScreen()
	{
		//Clear colour and buffer bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int RenderEngine::GetSamplerSlot(std::string SamplerName)
	{
		return SamplerMap.find(SamplerName)->second;
	}

	void RenderEngine::UpdateUniformStruct(Transform * transform, Material * material, Shader* shader, std::string& UniformName, std::string& UniformType)
	{
		std::cerr << UniformName << ": Illegal Argument" << std::endl;
	}
}