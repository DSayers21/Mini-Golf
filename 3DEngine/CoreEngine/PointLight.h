#pragma once

//Includes
#include "BaseLight.h"
#include "Attenuation.h"
#include "Vector3f.h"

namespace D3DEngine
{
	//Inherit from Base Light
	class PointLight : public BaseLight
	{
	public:
		//Constructors
		PointLight(ShaderList* shaderList);
		PointLight(ShaderList* shaderList, Vector3f colour, float intensity, Attenuation& attenuation);
		//Destructor
		~PointLight();
	};
}