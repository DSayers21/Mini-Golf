#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class ForwardPoint : public Shader
	{
	public:
		ForwardPoint();
		~ForwardPoint();
		void UpdateUniforms(Transform transform, Material material);
	};
}