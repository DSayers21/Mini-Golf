#include "ForwardPoint.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardPoint::ForwardPoint()
	{
		AddVertexShaderFromFile("Forward-Point.vert");
		AddFragmentShaderFromFile("Forward-Point.frag");

		//Set Attribs
		SetAttribLocation("Postion", 0);
		SetAttribLocation("TexCoord", 1);
		SetAttribLocation("Normal", 2);

		CompileShader();
		//Uniforms
		AddUniform("Model");
		AddUniform("MVP");

		//Specular Reflection
		AddUniform("SpecularIntensity");
		AddUniform("SpecularExponent");
		AddUniform("EyePos");

		//Point Light
		AddUniform("pointLight.Light.Colour");
		AddUniform("pointLight.Light.Intensity");
		AddUniform("pointLight.Atten.Constant");
		AddUniform("pointLight.Atten.Linear");
		AddUniform("pointLight.Atten.Exponent");
		AddUniform("pointLight.Position");
		AddUniform("pointLight.Range");
	}

	ForwardPoint::~ForwardPoint()
	{
	}

	void ForwardPoint::UpdateUniforms(Transform transform, Material material)
	{
		material.GetTexture()->Bind();

		Matrix4f WorldMatrix = transform.GetTransformation();
		Matrix4f ProjectedMatrix = GetRenderEngine()->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("Model", WorldMatrix);
		SetUniformM4("MVP", ProjectedMatrix);
		//Specular Reflection
		SetUniformF("SpecularIntensity", material.GetSpecularIntensity());
		SetUniformF("SpecularExponent", material.GetSpecularExponent());
		SetUniformV("EyePos", *GetRenderEngine()->GetCamera()->GetTransform()->GetPosition());
		//Point Light
		SetUniformPL("pointLight", GetRenderEngine()->GetActiveLight());
	}
}