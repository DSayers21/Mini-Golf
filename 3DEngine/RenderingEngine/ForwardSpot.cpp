#include "ForwardSpot.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardSpot::ForwardSpot()
	{
		AddVertexShaderFromFile("Forward-Spot.vert");
		AddFragmentShaderFromFile("Forward-Spot.frag");

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
		AddUniform("spotLight.PLight.Light.Colour");
		AddUniform("spotLight.PLight.Light.Intensity");
		AddUniform("spotLight.PLight.Atten.Constant");
		AddUniform("spotLight.PLight.Atten.Linear");
		AddUniform("spotLight.PLight.Atten.Exponent");
		AddUniform("spotLight.PLight.Position");
		AddUniform("spotLight.PLight.Range");

		AddUniform("spotLight.Direction");
		AddUniform("spotLight.Cutoff");
	}

	ForwardSpot::~ForwardSpot()
	{
	}

	void ForwardSpot::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		material->GetTexture("Diffuse").Bind();

		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("Model", WorldMatrix);
		SetUniformM4("MVP", ProjectedMatrix);
		//Specular Reflection
		SetUniformF("SpecularIntensity", material->GetFloat("SpecularIntensity"));
		SetUniformF("SpecularExponent", material->GetFloat("SpecularExponent"));
		SetUniformV("EyePos", renderEngine->GetCamera()->GetTransform()->GetTransformedPos());
		//Spot Light
		SetUniformSL("spotLight", renderEngine->GetActiveLight());
	}
}