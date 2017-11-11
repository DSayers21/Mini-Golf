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
		//Spot Light
		m_ShaderSpotLight = new ForwardSpot();
		m_ShaderSpotLight->SetRenderEngine(this);
		//Setup Lighting
		m_AmbientLight = Vector3f(0.2f, 0.2f, 0.2f);
		m_ActiveDirectionalLight = DirectionalLight(BaseLight(Vector3f(0, 0,1), 0.4f), Vector3f(1,1,1));
		m_ActivePointLight = PointLight(BaseLight(Vector3f(0, 1, 0), 0.9f), Attenuation(0, 0, 1), Vector3f(5, 0, 5), 100);

		m_SpotLight = SpotLight(PointLight(BaseLight(Vector3f(0, 1, 1), 0.4f), Attenuation(0, 0, .1), Vector3f(7, 0, 7), 100),
			Vector3f(1,0,0), 0.7);
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render(GameObject * Object)
	{
		ClearScreen();
		ClearLightList();

		Object->AddToRenderingEngine(this);	//Temp

		Object->Draw(m_ShaderForwardAmbient);

		//
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE); //Existing colour times one, plus other colour times one
		glDepthMask(false);			 //Disbale writing to the depth buffer
		glDepthFunc(GL_EQUAL);		 //Only change the pixel, if it has the exact same depth value
		//Any Code here will be blended into the image

		//Draw All Directional Lights
		for (int i = 0; i < m_DirectionalLights.size(); i++)
		{
			m_ActiveDirectionalLight = *m_DirectionalLights[i];
			Object->Draw(m_ShaderForwardDirectional);
		}

		for (int i = 0; i < m_PointLights.size(); i++)
		{
			m_ActivePointLight = *m_PointLights[i];
			Object->Draw(m_ShaderPointLight);
		}
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

	void RenderEngine::ClearLightList()
	{
		m_DirectionalLights.clear();
		m_PointLights.clear();
	}
}