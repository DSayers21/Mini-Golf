#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		//m_Renderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
		MappedValues();
		InitGraphics();

		m_ShaderList = new ShaderList();

		//Ambient Light
		m_ShaderForwardAmbient = new Shader("Forward-Ambient", m_ShaderList);
		AddVector3f("AmbientIntensity", Vector3f(0.6f, 0.6f, 0.6f));

		SamplerMap = std::map<std::string, int>();
		SamplerMap.insert(std::pair<std::string, int>("Diffuse", 0));
	}

	RenderEngine::~RenderEngine()
	{
		std::cerr << "Destructor: Render Engine" << std::endl;

	}

	void RenderOne(RenderEngine* self, std::vector<BaseLight*>& Lights, BaseLight* ActiveLight, GameObject * Object, int i)
	{
		//Draw All Lights

		self->SetActiveLight(Lights[i]);
		Object->Draw(self->GetActiveLight()->GetShader(), self);
		
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


		std::vector<std::thread> Threads = std::vector<std::thread>();


		//Draw All Lights
		for (int i = 0; i < m_Lights.size(); i++)
		{
			RenderOne( this, m_Lights, ActiveLight, Object, i);
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

	int RenderEngine::GetSamplerSlot(const std::string& SamplerName)
	{
		return SamplerMap.find(SamplerName)->second;
	}

	void RenderEngine::UpdateUniformStruct(Transform * transform, Material * material, Shader* shader, std::string& UniformName, std::string& UniformType)
	{
		//std::cerr << UniformName << ": Illegal Argument" << std::endl;
	}

	void RenderEngine::ResetEngine()
	{
		delete m_ShaderList;

		//Permanent Structures
		std::vector<BaseLight*> m_Lights = std::vector<BaseLight*>();

		for (int i = 0; i < m_Lights.size(); i++)
		{
			delete m_Lights[i];
			m_Lights.erase(m_Lights.begin() + i);
		}


		ActiveLight = nullptr;
	}
}