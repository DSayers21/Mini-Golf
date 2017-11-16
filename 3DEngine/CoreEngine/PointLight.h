#pragma once
#include "BaseLight.h"
#include "Attenuation.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class PointLight : public BaseLight
	{
	public:
		PointLight(ShaderList* shaderList);
		PointLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation);
		~PointLight();
	};
}