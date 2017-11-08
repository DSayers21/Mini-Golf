#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class BasicShader : public Shader
	{
	public:
		BasicShader();
		~BasicShader();
		void UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material);
	};
}
