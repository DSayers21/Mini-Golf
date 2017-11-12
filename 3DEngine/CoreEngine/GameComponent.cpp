#include "GameComponent.h"
#include "RenderEngine.h"
#include "Shader.h"
#include "GameObject.h"

namespace D3DEngine
{
	GameComponent::GameComponent()
	{
	}


	GameComponent::~GameComponent()
	{
	}

	void GameComponent::Input(GetInput* input, float Delta)
	{
	}

	void GameComponent::Update(float Delta)
	{
	}

	void GameComponent::Draw(Shader* shader)
	{
	}

	void GameComponent::AddToRenderingEngine(RenderEngine * renderEngine)
	{
	}
}