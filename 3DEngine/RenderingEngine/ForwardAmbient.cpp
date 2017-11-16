#include "ForwardAmbient.h"
#include "RenderEngine.h"

namespace D3DEngine
{
	ForwardAmbient::ForwardAmbient()
	{
		InitShader("Forward-Ambient");
	}

	ForwardAmbient::~ForwardAmbient()
	{
	}

	void ForwardAmbient::UpdateUniforms(Transform* transform, Material* material, RenderEngine* renderEngine)
	{
		material->GetTexture("Diffuse")->Bind();
		Matrix4f WorldMatrix = transform->GetTransformation();
		Matrix4f ProjectedMatrix = renderEngine->GetCamera()->GetViewProjection().Mult(WorldMatrix);

		SetUniformM4("MVP", ProjectedMatrix);
		SetUniformV("AmbientIntensity", renderEngine->GetAmbientLight());
	}
}