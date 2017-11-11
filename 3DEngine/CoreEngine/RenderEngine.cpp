#include "RenderEngine.h"

namespace D3DEngine
{
	RenderEngine::RenderEngine()
	{
		m_Camera = new Camera();
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
}