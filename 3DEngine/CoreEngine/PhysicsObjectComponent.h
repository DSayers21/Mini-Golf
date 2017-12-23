#pragma once

//Includes
#include "GameComponent.h"
#include "PhysicsObject.h"

namespace D3DEngine
{
	//Inherit from Game Component
	class PhysicsObjectComponent : public GameComponent
	{
	public:
		//Constructor
		PhysicsObjectComponent(PhysicsObject* engine, bool Control = false);
		//Destructor
		~PhysicsObjectComponent();
		//Update the object
		void Update(float Delta);

	private:
		//Pointer to the physics object
		PhysicsObject* m_PhysicsObject;
	};
}