#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
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
		Object->Draw(m_ShaderForwardAmbient);

	}

	void RenderEngine::CameraInput(Input& input, float Delta)
	{
		m_Camera->DoInput(input, Delta);
	}
}