#include "GameComponent.h"
#include "RenderEngine.h"
#include "Shader.h"

namespace D3DEngine
{
	GameComponent::GameComponent()
	{
	}


	GameComponent::~GameComponent()
	{
	}

	void GameComponent::Input(Transform transform, float Delta)
	{
	}

	void GameComponent::Update(Transform transform, float Delta)
	{
	}

	void GameComponent::Draw(Transform* transform, Shader* shader)
	{
	}

	void GameComponent::AddToRenderingEngine(RenderEngine * renderEngine)
	{
	}
}