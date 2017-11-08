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

		SetUniform("Transform", ProjectedMatrix);
		SetUniform("BaseColour", *material.GetColour());
		SetUniform("AmbientLight", m_AmbientLight);
	}
}