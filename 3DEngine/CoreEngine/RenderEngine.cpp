#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		InitGraphics();
		//m_Camera = new Camera(TO_RADIANS(70.0f), (float)800/600, 0.1f, 1000);
		//Ambient Light
		m_ShaderForwardAmbient = new ForwardAmbient();
		//Setup Lighting
		m_AmbientLight = Vector3f(0.2f, 0.2f, 0.2f);
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render(GameObject * Object)
	{
		ClearScreen();
		m_Lights.clear();

		Object->AddToRenderingEngine(this);

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
}