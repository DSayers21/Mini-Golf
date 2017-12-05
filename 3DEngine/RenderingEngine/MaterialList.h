#pragma once

#include "Material.h"

namespace D3DEngine
{
	class MaterialList
	{
	public:
		MaterialList();
		~MaterialList();

		void AddMaterial(const std::string& name, Material* material);

		bool IsLoaded(const std::string& name);

	private:
		std::map<std::string, Material*> m_MaterialList;
	};
}