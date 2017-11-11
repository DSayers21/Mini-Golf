#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class BasicShader : public Shader
	{
	public:
		BasicShader();
		~BasicShader();
		void UpdateUniforms(Transform transform, Material material);
	};
}
