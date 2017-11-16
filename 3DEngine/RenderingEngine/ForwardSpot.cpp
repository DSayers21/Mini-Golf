#include "ForwardSpot.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardSpot::ForwardSpot()
	{
		InitShader("Forward-Spot");
	}

	ForwardSpot::~ForwardSpot()
	{
	}

	void ForwardSpot::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		Shader::UpdateUniforms(transform, material, renderEngine);
	}
}