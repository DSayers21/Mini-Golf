#pragma once

#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class DirectionalLight : public BaseLight
	{
	public:
		DirectionalLight(ShaderList* shaderList);
		DirectionalLight(ShaderList* shaderList, Vector3f Colour, float Intensity);
		~DirectionalLight();
	};
}