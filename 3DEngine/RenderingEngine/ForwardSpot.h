#pragma once
#include "Shader.h"

namespace D3DEngine
{
	class ForwardSpot : public Shader
	{
	public:
		ForwardSpot();
		~ForwardSpot();
		void UpdateUniforms(Transform* transform, Material* material);
	};
}