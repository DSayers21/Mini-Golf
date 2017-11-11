#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		InitGraphics();
		m_Camera = new Camera(TO_RADIANS(70.0f), (float)800/600, 0.1f, 1000);
		//Ambient Light
		m_ShaderForwardAmbient = new ForwardAmbient();
		m_ShaderForwardAmbient->SetRenderEngine(this);
		//Directional Light
		m_ShaderForwardDirectional = new ForwardDirectional();
		m_ShaderForwardDirectional->SetRenderEngine(this);
		//Point Light
		m_ShaderPointLight = new ForwardPoint();
		m_ShaderPointLight->SetRenderEngine(this);

		//Setup Lighting
		m_AmbientLight = Vector3f(0.2f, 0.2f, 0.2f);
		m_DirectionalLight = DirectionalLight(BaseLight(Vector3f(0, 0,1), 0.4f), Vector3f(1,1,1));
		m_DirectionalLight2 = DirectionalLight(BaseLight(Vector3f(1, 0, 0), 0.4f), Vector3f(-1, 1, -1));
		m_PointLight = PointLight(BaseLight(Vector3f(0, 1, 0), 0.9f), Attenuation(0, 0, 1), Vector3f(5, 0, 5), 100);
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render(GameObject * Object)
	{
		ClearScreen();

		Object->Draw(m_ShaderForwardAmbient);

		//
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE); //Existing colour times one, plus other colour times one
		glDepthMask(false);			 //Disbale writing to the depth buffer
		glDepthFunc(GL_EQUAL);		 //Only change the pixel, if it has the exact same depth value
		//Any Code here will be blended into the image

		Object->Draw(m_ShaderForwardDirectional);

		//Swap Lights
		DirectionalLight Temp = m_DirectionalLight;
		m_DirectionalLight = m_DirectionalLight2;
		m_DirectionalLight2 = Temp;

		Object->Draw(m_ShaderForwardDirectional);

		Temp = m_DirectionalLight;
		m_DirectionalLight = m_DirectionalLight2;
		m_DirectionalLight2 = Temp;

		//Point Light
		Object->Draw(m_ShaderPointLight);

		//end of blending
		glDepthFunc(GL_LESS);
		glDepthMask(true);			 //Enable writing to the depth buffer
		glDisable(GL_BLEND);
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