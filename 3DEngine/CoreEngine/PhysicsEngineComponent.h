#pragma once

//Includes
#include "GameComponent.h"
#include "PhysicsEngine.h"

namespace D3DEngine
{
	//Inherit from Game Component
	class PhysicsEngineComponent : public GameComponent
	{
	public:
		//Constructor
		PhysicsEngineComponent(PhysicsEngine* engine);
		//Destructor
		~PhysicsEngineComponent();
		//Update function
		virtual void Update(float Delta);

		//Getters
		inline PhysicsEngine* GetPhysicsEngine() { return m_PhysicsEngine; }

	private:
		//Pointer to the physics engine
		PhysicsEngine* m_PhysicsEngine;
	};
}