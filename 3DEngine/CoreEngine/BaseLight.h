#pragma once

#include "Vector3f.h"
#include "GameComponent.h"
#include "Attenuation.h"
#include "ResourceManagement/ShaderList.h"
#include "Shader.h"

namespace D3DEngine
{
	class BaseLight : public GameComponent
	{
	public:
		BaseLight() {}
		BaseLight(ShaderList* shaderList);
		BaseLight(ShaderList* shaderList, Vector3f colour, float intensity);
		~BaseLight();

		void AddToRenderingEngine(RenderEngine * renderEngine);
		float CalcRange();

		//Getters
		inline Vector3f GetColour() { return m_Colour; }
		inline float GetIntensity() { return m_Intensity; }
		inline Shader* GetShader() { return m_Shader; }
		inline Attenuation GetAttenuation() { return m_Attenuation; }
		inline float GetRange() { return m_Range; }
		Vector3f GetDirection() { return GetTransform()->GetTransformedRot().GetForward(); }
		inline float& GetCutoff() { return m_Cutoff; }
		//Setters
		inline void SetColour(Vector3f colour) { m_Colour = colour; }
		inline void SetIntensity(float intensity) { m_Intensity = intensity; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }
		inline void SetAttenuation(Attenuation& attenuation) { m_Attenuation = attenuation; }
		inline void SetRange(float& Range) { m_Range = Range; }
		inline void SetCutoff(float cutoff) { m_Cutoff = cutoff; }
		
	protected:
		Shader* m_Shader;
		Vector3f m_Colour;
		float m_Intensity;
		//Point Extras
		Attenuation m_Attenuation;
		float m_Range;
		//Spot Extras
		float m_Cutoff;
		const static int COLOUR_DEPTH = 256;
	};
}