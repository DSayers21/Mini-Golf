#pragma once

#include "MainGame.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include "FreeLook.h"
#include "PhysicsEngineComponent.h"
#include "PhysicsObjectComponent.h"

class TestGame : public MainGame
{
public:
	TestGame();
	~TestGame();

	void Init(D3DEngine::RenderEngine* renderEngine);
	void Input(D3DEngine::GetInput* input, float Delta);

private:
};

