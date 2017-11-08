#pragma once

#include "Texture.h"
#include "Vector3f.h"

namespace D3DEngine
{
	class Material
	{
	public:
		Material(Texture texture, Vector3f colour);
		~Material();

		//Getters
		Texture* GetTexture() { return &m_Texture; }
		Vector3f* GetColour() { return &m_Colour; }
		//Setters
		void SetTexture(Texture texture) { m_Texture = texture; }
		void SetColour(Vector3f colour) { m_Colour = colour; }

	private:
		Texture m_Texture;
		Vector3f m_Colour;
	};
}
