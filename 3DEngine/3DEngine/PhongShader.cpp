#include "PhongShader.h"

namespace D3DEngine
{
	PhongShader::PhongShader()
	{
		Shader();
		AddVertexShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.vert"));
		AddFragmentShader(D3DEngine::ResourceLoader::LoadShader("PhongShader.frag"));
		CompileShader();
		//Uniforms
		AddUniform("Transform");
		AddUniform("BaseColour");

		AddUniform("AmbientLight");

		AddUniform("directionalLight.Light.Colour");
		AddUniform("directionalLight.Light.Intensity");
		AddUniform("directionalLight.Direction");
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

		SetUniformM4("Transform", ProjectedMatrix);
		SetUniformV("BaseColour", *material.GetColour());
		SetUniformV("AmbientLight", m_AmbientLight);
		SetUniform("directionalLight", m_DirectionalLight);
	}

	void PhongShader::SetUniform(std::string UniformName, DirectionalLight DirLight)
	{
		SetUniform(UniformName + ".Light", DirLight.GetBaseLight());
		SetUniformV(UniformName + ".Direction", DirLight.GetDirection());
	}

	void PhongShader::SetUniform(std::string UniformName, BaseLight BaseLight)
	{
		SetUniformV(UniformName + ".Colour", BaseLight.GetColour());
		SetUniformF(UniformName + ".Intensity", BaseLight.GetIntensity());
	}
}