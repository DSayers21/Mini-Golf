#pragma once
#include "BaseLight.h"
#include "Attenuation.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class PointLight : public BaseLight
	{
	public:
		PointLight();
		PointLight(Vector3f colour, float intensity, Attenuation& attenuation, Vector3f& Position, float Range);
		~PointLight();
	};
}