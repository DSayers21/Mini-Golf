#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		m_Camera = new Camera(TO_RADIANS(70.0f), (float)800/600, 0.1f, 1000);
		BShade = new BasicShader();
		BShade->SetRenderEngine(this);
	}

	RenderEngine::~RenderEngine()
	{
	}

	void RenderEngine::Render(GameObject * Object)
	{
		Object->Draw(BShade);
	}

	void RenderEngine::CameraInput(Input& input, Time& time)
	{
		m_Camera->DoInput(input, time);
	}
}