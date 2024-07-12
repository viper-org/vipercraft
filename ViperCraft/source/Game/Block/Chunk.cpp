#include <Game/Block/Chunk.h>

namespace ViperCraft
{
	Chunk::Chunk()
		: mTiles{0}
		, mPosition(glm::vec3(0.f))
	{
	}

	Chunk::Chunk(glm::vec3 position)
		: mTiles{0}
		, mPosition(position)
	{
	}

	Tile*& Chunk::getTile(glm::vec3 position)
	{
		glm::vec3 offset = position - mPosition;
		
		return mTiles[(int)std::abs(offset.x)][(int)std::abs(offset.y)][(int)std::abs(offset.z)];
	}

	void Chunk::drawAll(ViperGL::RenderQueue& renderQueue)
	{
		glm::vec3 position = mPosition;
		for (auto& yz : mTiles)
		{
			for (auto& z : yz)
			{
				for (auto tile : z)
				{
					if (tile && tile->getRenderableId() != -1) // checking that it isnt air
						renderQueue.drawRenderable(tile->getRenderableId(), position);
					position.z += 1;
				}
				position.z = mPosition.z;
				position.y += 1;
			}
			position.y = mPosition.y;
			position.x += 1;
		}
	}
}