#pragma once

#include <string>

namespace ViperGL
{
	class Voxel
	{
	friend class RenderQueue;
	public:
		Voxel(float x, float y, float z, std::string textureName);

	private:
		float mX;
		float mY;
		float mZ;

		std::string mTextureName;
	};
}