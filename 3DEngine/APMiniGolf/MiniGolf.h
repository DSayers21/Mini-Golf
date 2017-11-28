#pragma once

#include "MainGame.h"

class MiniGolf : public MainGame
{
public:
	MiniGolf();
	~MiniGolf();

	void Init(D3DEngine::RenderEngine* renderEngine, D3DEngine::PhysicsEngine* physicsEngine);
	void Input(D3DEngine::GetInput* input, float Delta);
};