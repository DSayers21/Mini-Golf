#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class ForwardDirectional : public Shader
	{
	public:
		ForwardDirectional();
		~ForwardDirectional();
		void UpdateUniforms(Transform* transform, Material* material);
		void SetUniformDL(std::string UniformName, BaseLight * DirLight);
	};
}