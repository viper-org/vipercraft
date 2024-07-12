#pragma once

#include <string>

namespace ViperGL
{
	class Voxel
	{
	friend class RenderQueue;
	public:
		Voxel(std::string_view textureName);

	private:
		std::string mTextureName;
	};
}