#pragma once
#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class SpotLight : public BaseLight
	{
	public:
		SpotLight();
		SpotLight(Vector3f colour, float intensity, Attenuation& attenuation, Vector3f& Position, Vector3f direction, float Range, float cutoff);
		~SpotLight();
	};
}