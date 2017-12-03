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
		std::cerr << "Destructor: Game Component" << std::endl;
	}

	void GameComponent::Input(GetInput* input, float Delta)
	{
	}

	void GameComponent::Update(float Delta)
	{
	}

	void GameComponent::Draw(Shader* shader, RenderEngine* renderEngine)
	{
	}

	void GameComponent::AddToEngine(MainComp * mainComp)
	{
	}
}