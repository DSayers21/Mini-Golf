#pragma once
#include "Shader.h"
#include "Transform.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "MathBasics.h"

namespace D3DEngine
{
	class PhongShader : public Shader
	{
	public:
		PhongShader();
		~PhongShader();
		void UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material);

		void SetUniformPL(std::string UniformName, PointLight& pointLight);

		void SetUniformSL(std::string UniformName, SpotLight & spotLight);

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline DirectionalLight GetDirectionalLight() { return m_DirectionalLight; }
		//Setters
		inline void SetAmbientLight(Vector3f ambientlight) { m_AmbientLight = ambientlight; }
		inline void SetDirectionalLight(DirectionalLight dirLight) { m_DirectionalLight = dirLight; }
		inline void SetTransform(Transform* Trans) { m_Transform = Trans; }
		void SetPointLight(PointLight* pointLights, int NumOfPointLights);
		void SetSpotLight(SpotLight * spotLights, int NumOfSpotLights);
	private:
		Vector3f m_AmbientLight = Vector3f(0.1,0.1,0.1);
		DirectionalLight m_DirectionalLight;;
		Transform* m_Transform;
		PointLight* m_PointLights;
		SpotLight* m_SpotLights;

		static const int MAX_POINT_LIGHTS = 4;
		static const int MAX_SPOT_LIGHTS = 4;
	};
}