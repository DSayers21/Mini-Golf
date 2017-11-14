#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class ForwardAmbient : public Shader
	{
	public:
		ForwardAmbient();
		~ForwardAmbient();
		void UpdateUniforms(Transform* transform, Material material);
	};
}