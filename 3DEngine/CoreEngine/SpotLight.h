#pragma once

//Includes
#include "BaseLight.h"
#include "Vector3f.h"

namespace D3DEngine
{
	//Inherit from Base Light
	class SpotLight : public BaseLight
	{
	public:
		//Constructors
		SpotLight(ShaderList* shaderList);
		SpotLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation, float cutoff);
		//Destructors
		~SpotLight();
	};
}