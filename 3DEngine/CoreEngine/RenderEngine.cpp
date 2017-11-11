#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		InitGraphics();
		m_Camera = new Camera(TO_RADIANS(70.0f), (float)800/600, 0.1f, 1000);
		m_ShaderForwardAmbient = new ForwardAmbient();
		m_ShaderForwardAmbient->SetRenderEngine(this);
		m_AmbientLight = Vector3f(0.2f, 0.2f, 0.2f);
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render(GameObject * Object)
	{
		ClearScreen();
		Object->Draw(m_ShaderForwardAmbient);

		glEnable(GL_BLEND);

	}

	void RenderEngine::CameraInput(Input& input, float Delta)
	{
		m_Camera->DoInput(input, Delta);
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