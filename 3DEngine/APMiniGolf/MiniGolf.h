#pragma once

#include "MainGame.h"
#include "MeshRenderer.h"
#include "FreeLook.h"
#include "PhysicsEngineComponent.h"
#include "PhysicsObjectComponent.h"

class MiniGolf : public MainGame
{
public:
	MiniGolf();
	~MiniGolf();

	void Init(D3DEngine::RenderEngine* renderEngine);
	void Input(D3DEngine::GetInput* input, float Delta);
};

