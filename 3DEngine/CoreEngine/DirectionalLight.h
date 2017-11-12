#pragma once

#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class DirectionalLight : public BaseLight
	{
	public:
		DirectionalLight();
		DirectionalLight(Vector3f Colour, float Intensity);
		~DirectionalLight();
	};
}