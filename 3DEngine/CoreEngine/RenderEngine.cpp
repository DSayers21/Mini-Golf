#include "RenderEngine.h"
#include "TextRendering.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine(Window* Window)
	{
		m_Window = Window;
		//m_Renderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
		MappedValues();
		InitGraphics();

		m_ShaderList = new ShaderList();

		//Ambient Light
		m_ShaderForwardAmbient = new Shader("Forward-Ambient", m_ShaderList);
		AddVector3f("AmbientIntensity", Vector3f(0.6f, 0.6f, 0.6f));

		SamplerMap = std::map<std::string, int>();
		SamplerMap.insert(std::pair<std::string, int>("Diffuse", 0));

		m_TextRender = new TextRendering(m_Window);
	}

	RenderEngine::~RenderEngine()
	{
		std::cerr << "Destructor: Render Engine" << std::endl;
		delete m_ShaderForwardAmbient;
		delete m_ShaderList;
		delete m_TextRender;
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

		//Render All Text
		RenderText();
	}

	void RenderEngine::RenderText()
	{
		//Render All Text
		for (std::pair<std::string, TextToRender> element : m_Text)
		{
			m_TextRender->Render(element.second.m_Text, element.second.m_Colour, element.second.X, element.second.Y);
		}

		glFlush();
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

	void RenderEngine::AddText(std::string Name, TextToRender Content)
	{
		if (m_Text.find(Name) == m_Text.end()) 
		{
			//Not found
			m_Text.insert(std::pair<std::string, TextToRender>(Name, Content));
		}
		else 
		{
			//Found
			m_Text.find(Name)->second = Content;
		}
	}
	void RenderEngine::RemoveText(std::string Name)
	{
		for (std::map<std::string, TextToRender>::iterator it = m_Text.begin(); it != m_Text.end();)
		{
			if ((it->first) == Name)
				it = m_Text.erase(it);
			else
				it++;
		}
	}

	void RenderEngine::ResetEngine()
	{
		m_Lights.clear();
		ActiveLight = nullptr;
	}
}