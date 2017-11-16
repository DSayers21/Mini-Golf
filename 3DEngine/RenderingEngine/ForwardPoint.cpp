#include "ForwardPoint.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardPoint::ForwardPoint()
	{
		InitShader("Forward-Point");
	}

	ForwardPoint::~ForwardPoint()
	{
	}

	void ForwardPoint::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		material->GetTexture("Diffuse")->Bind();

		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("Model", WorldMatrix);
		SetUniformM4("MVP", ProjectedMatrix);
		//Specular Reflection
		SetUniformF("SpecularIntensity", material->GetFloat("SpecularIntensity"));
		SetUniformF("SpecularExponent", material->GetFloat("SpecularExponent"));
		SetUniformV("EyePos", renderEngine->GetCamera()->GetTransform()->GetTransformedPos());
		//Point Light
		SetUniformPL("pointLight", renderEngine->GetActiveLight());
	}
}