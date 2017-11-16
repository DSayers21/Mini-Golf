#include "ForwardAmbient.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardAmbient::ForwardAmbient()
	{
		InitShader("Forward-Ambient");
	}

	ForwardAmbient::~ForwardAmbient()
	{
	}

	void ForwardAmbient::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		Shader::UpdateUniforms(transform, material, renderEngine);
	}
}