#include "BasicShader.h"

namespace D3DEngine
{
	BasicShader::BasicShader()
	{
		AddVertexShaderFromFile("BasicShader.vert");
		AddFragmentShaderFromFile("BasicShader.frag");
		CompileShader();
		//Uniforms
		AddUniform("Transform");
		AddUniform("Colour");
	}

	BasicShader::~BasicShader()
	{
	}

	void BasicShader::UpdateUniforms(Matrix4f WorldMatrix, Matrix4f ProjectedMatrix, Material material)
	{
		if (material.GetTexture() != NULL)
			material.GetTexture()->Bind();
		else
			RenderUtil::UnBindTextures();

		SetUniformM4("Transform", ProjectedMatrix);
		SetUniformV("Colour", *material.GetColour());
	}
}