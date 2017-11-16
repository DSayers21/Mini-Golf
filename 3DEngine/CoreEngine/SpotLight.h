#pragma once
#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class SpotLight : public BaseLight
	{
	public:
		SpotLight(ShaderList* shaderList);
		SpotLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation, float cutoff);
		~SpotLight();
	};
}