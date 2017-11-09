#pragma once
#include "Shader.h"
#include "Transform.h"
#include "PointLight.h"
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

		//Getters
		inline Vector3f GetAmbientLight() { return m_AmbientLight; }
		inline DirectionalLight GetDirectionalLight() { return m_DirectionalLight; }
		//Setters
		inline void SetAmbientLight(Vector3f ambientlight) { m_AmbientLight = ambientlight; }
		inline void SetDirectionalLight(DirectionalLight dirLight) { m_DirectionalLight = dirLight; }
		inline void SetTransform(Transform* Trans) { m_Transform = Trans; }
		void SetPointLight(PointLight* pointLights, int NumOfPointLights);
	private:
		Vector3f m_AmbientLight = Vector3f(0.1,0.1,0.1);
		DirectionalLight m_DirectionalLight;;
		Transform* m_Transform;
		static const int MAX_POINT_LIGHTS = 4;
		PointLight* m_PointLights;
	};
}