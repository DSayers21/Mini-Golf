//Includes
#include "RenderEngine.h"
#include "TextRendering.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine(Window* Window)
	{
		//Set Window
		m_Window = Window;

		//Create Mapped Values
		MappedValues();

		//Init Graphics
		InitGraphics();
		//Create shader list
		m_ShaderList = new ShaderList();

		//Create Ambient Light
		m_ShaderForwardAmbient = new Shader("Forward-Ambient", m_ShaderList);
		AddVector3f("AmbientIntensity", Vector3f(0.6f, 0.6f, 0.6f));

		//Setup Sampler Map
		m_SamplerMap = std::map<std::string, int>();
		m_SamplerMap.insert(std::pair<std::string, int>("Diffuse", 0));

		//Create text renderer
		m_TextRender = new TextRendering(m_Window);
	}

	RenderEngine::~RenderEngine()
	{
		//Display Message
		std::cerr << "Destructor: Render Engine" << std::endl;
		//Delete all aspects
		delete m_ShaderForwardAmbient;
		delete m_ShaderList;
		delete m_TextRender;
	}

	void RenderOne(RenderEngine* self, std::vector<BaseLight*>& Lights, BaseLight* ActiveLight, GameObject * Object, int i)
	{
		//Draw Single Lights
		self->SetActiveLight(Lights[i]);
		Object->Draw(self->GetActiveLight()->GetShader(), self);
		
	}
	void RenderEngine::Render(GameObject * Object)
	{
		//Clear Screen
		ClearScreen();

		glUseProgramObjectARB(0);
		//Render All Text
		RenderText();

		//Draw all objects with ambient light
		Object->Draw(m_ShaderForwardAmbient, this);


		glEnable(GL_BLEND);			 //Set to blend
		glBlendFunc(GL_ONE, GL_ONE); //Existing colour times one, plus other colour times one
		glDepthMask(false);			 //Disbale writing to the depth buffer
		glDepthFunc(GL_EQUAL);		 //Only change the pixel, if it has the exact same depth value
		
		//Any Code here will be blended into the image

		//Draw All Lights
		for (int i = 0; i < m_Lights.size(); i++)
		{
			RenderOne( this, m_Lights, m_ActiveLight, Object, i);
			m_ActiveLight->GetShader()->UnBind();
		}
		
		//End of blending
		glDepthFunc(GL_LESS);
		glDepthMask(true);			 //Enable writing to the depth buffer
		
		glDisable(GL_BLEND);
	}

	void RenderEngine::RenderText()
	{
		//Render All Text
		for (std::pair<std::string, TextToRender> element : m_Text)
			m_TextRender->Render(element.second.m_Text, element.second.m_Colour, element.second.X, element.second.Y);
		//Flush
		glFlush();
	}

	void RenderEngine::InitGraphics()
	{
		//Set clear colour
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		//Setup graphics settings
		glFrontFace(GL_CW);				//Clockwise
		glCullFace(GL_BACK);			//Cull back faces
		glEnable(GL_CULL_FACE);		
		glEnable(GL_DEPTH_TEST);		//Depths
		glEnable(GL_TEXTURE_2D);		//Enable Textures
		SetTextures(true);
		glEnable(GL_DEPTH_CLAMP);		//Enable Depth Clamp
	}

	void RenderEngine::SetTextures(bool Enabled)
	{
		//Set textures
		(Enabled) ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
	}

	void RenderEngine::ClearScreen()
	{
		//Clear colour and buffer bits
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	int RenderEngine::GetSamplerSlot(const std::string& SamplerName)
	{
		//Get the sampler slot at the keyed position
		return m_SamplerMap.find(SamplerName)->second;
	}

	void RenderEngine::UpdateUniformStruct(Transform * transform, Material * material, Shader* shader, std::string& UniformName, std::string& UniformType)
	{
		//Empty (Extra space to handle for struct updates)
	}

	void RenderEngine::AddText(const std::string& Name, TextToRender Content)
	{
		//Check if text is already in UI
		if (m_Text.find(Name) == m_Text.end()) 
		{
			//Not found, add the text
			m_Text.insert(std::pair<std::string, TextToRender>(Name, Content));
		}
		else 
		{
			//Found, update the text
			m_Text.find(Name)->second = Content;
		}
	}
	void RenderEngine::RemoveText(const std::string& Name)
	{
		//Remove Text at given key
		for (std::map<std::string, TextToRender>::iterator it = m_Text.begin(); it != m_Text.end();)
		{
			if ((it->first) == Name)
				it = m_Text.erase(it);
			else
				it++;
		}
	}

	void RenderEngine::RemoveAllText()
	{
		//Clear all text from UI
		m_Text.clear();
	}

	void RenderEngine::ResetEngine()
	{
		//Clear all lights
		m_Lights.clear();
		//Set Active Light to nullptr
		m_ActiveLight = nullptr;
	}
}