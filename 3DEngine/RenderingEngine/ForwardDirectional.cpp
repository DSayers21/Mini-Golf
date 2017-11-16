#include "ForwardDirectional.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardDirectional::ForwardDirectional()
	{
		InitShader("Forward-Directional");
	}

	ForwardDirectional::~ForwardDirectional()
	{
	}

	void ForwardDirectional::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		Shader::UpdateUniforms(transform, material, renderEngine);
	}
}