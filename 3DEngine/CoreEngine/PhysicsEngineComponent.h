#pragma once

#include "GameComponent.h"
#include "PhysicsEngine.h"

namespace D3DEngine
{
	class PhysicsEngineComponent : public GameComponent
	{
	public:
		PhysicsEngineComponent(PhysicsEngine* engine);
		~PhysicsEngineComponent();

		virtual void Update(float Delta);

		//Getters
		inline PhysicsEngine* GetPhysicsEngine() { return m_PhysicsEngine; }

	private:
		PhysicsEngine* m_PhysicsEngine;
	};
}