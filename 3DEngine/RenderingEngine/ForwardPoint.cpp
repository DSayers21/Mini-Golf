#include "ForwardPoint.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardPoint::ForwardPoint()
	{
		InitShader("Forward-Point");
	}

	ForwardPoint::~ForwardPoint()
	{
	}

	void ForwardPoint::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		Shader::UpdateUniforms(transform, material, renderEngine);
	}
}