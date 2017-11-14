#pragma once

#include "MainGame.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"

class TestGame : public MainGame
{
public:
	TestGame();
	~TestGame();

	void Init();
	void Input(D3DEngine::GetInput* input, float Delta);

private:
};

