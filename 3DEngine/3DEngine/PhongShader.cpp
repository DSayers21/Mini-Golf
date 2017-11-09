#include "PhongShader.h"

namespace D3DEngine
{
	PhongShader::PhongShader()
	{
		m_DirectionalLight = DirectionalLight(BaseLight(Vector3f(1, 1, 1), .1), Vector3f(1, 1, 1));

		AddVertexShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.vert"));
		AddFragmentShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.frag"));
		CompileShader();
		//Uniforms
		AddUniform("Transform");
		AddUniform("TransformProjected");

		AddUniform("BaseColour");

		AddUniform("AmbientLight");

		AddUniform("directionalLight.Light.Colour");
		AddUniform("directionalLight.Light.Intensity");
		AddUniform("directionalLight.Direction");

		AddUniform("SpecularIntensity");
		AddUniform("SpecularExponent");
		AddUniform("EyePos");

		//Init array of point lights
		for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			AddUniform("PointLights[" + std::to_string(i) + "].Light.Colour");
			AddUniform("PointLights[" + std::to_string(i) + "].Light.Intensity");
			AddUniform("PointLights[" + std::to_string(i) + "].Atten.Constant");
			AddUniform("PointLights[" + std::to_string(i) + "].Atten.Linear");
			AddUniform("PointLights[" + std::to_string(i) + "].Atten.Exponent");
			AddUniform("PointLights[" + std::to_string(i) + "].Position");
		}
	}

	PhongShader::~PhongShader()
	{
	}

	void PhongShader::UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material)
	{
		if (material.GetTexture() != NULL)
			material.GetTexture()->Bind();
		else
			RenderUtil::UnBindTextures();

		SetUniformM4("Transform", WorldMatrix);
		SetUniformM4("TransformProjected", ProjectedMatrix);
		SetUniformV("BaseColour", *material.GetColour());
		//Lighting
		SetUniformV("AmbientLight", m_AmbientLight);
		SetUniformDL("directionalLight", m_DirectionalLight);
		for (int i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			int T = ARRAY_SIZE(m_PointLights);
			PointLight Temp = m_PointLights[i];
			SetUniformPL("PointLights[" + std::to_string(i) + "]", Temp);
		}
		//Specular Reflection
		SetUniformF("SpecularIntensity", material.GetSpecularIntensity());
		SetUniformF("SpecularExponent", material.GetSpecularExponent());
		SetUniformV("EyePos", m_Transform->GetCamera()->GetPos());
	}

	void PhongShader::SetUniformPL(std::string UniformName, PointLight& pointLight)
	{
		SetUniformBL(UniformName + ".Light", pointLight.GetBaseLight());
		//Attenuation
		SetUniformF(UniformName + ".Atten.Constant", pointLight.GetAttenuation().GetConstant());
		SetUniformF(UniformName + ".Atten.Linear", pointLight.GetAttenuation().GetLinear());
		SetUniformF(UniformName + ".Atten.Exponent", pointLight.GetAttenuation().GetExponent());

		SetUniformV(UniformName + ".Position", pointLight.GetPosition());
	}

	void PhongShader::SetPointLight(PointLight* pointLights, int NumOfPointLights)
	{
		if (NumOfPointLights > MAX_POINT_LIGHTS)
		{
			std::cerr << "Error: Too Many Point Lights. Max Allowed Is: " << MAX_POINT_LIGHTS
				<< " You passed in: " << NumOfPointLights - MAX_POINT_LIGHTS << std::endl;
			return;
		}
		//Assign PointLights
		//for(int i = 0; i < NumOfPointLights; i++)
		m_PointLights = pointLights;
	}
}