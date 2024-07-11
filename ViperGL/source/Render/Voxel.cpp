#include <ViperGL/Render/Voxel.h>

namespace ViperGL
{
	Voxel::Voxel(float x, float y, float z, std::string textureName)
		: mX(x)
		, mY(y)
		, mZ(z)
		, mTextureName(std::move(textureName))
	{
	}
}