#include <Game/Block/Chunk.h>

#include <ViperCraft/ViperCraft.h>

namespace ViperCraft
{
	Chunk::Chunk()
		: mTiles{0}
		, mPosition(glm::vec3(0.f))
		, mRenderBuffer(-1)
		, mTransparentRenderBuffer(-1)
	{
	}

	Chunk::Chunk(glm::vec3 position)
		: mTiles{0}
		, mPosition(position)
		, mRenderBuffer(-1)
		, mTransparentRenderBuffer(-1)
	{
	}

	void Chunk::beginRendering()
	{
		mRenderBuffer = ViperCraft::GetInstance()->getRenderQueue()->newBuffer();
		mTransparentRenderBuffer = ViperCraft::GetInstance()->getRenderQueue()->newBuffer();
	}

	void Chunk::draw()
	{
		ViperCraft::GetInstance()->getRenderQueue()->draw(mRenderBuffer);
		ViperCraft::GetInstance()->getRenderQueue()->draw(mTransparentRenderBuffer);
	}

	glm::vec3 Chunk::getPosition()
	{
		return mPosition;
	}

	Tile*& Chunk::getTile(glm::vec3 position)
	{
		glm::vec3 offset = position - mPosition;

		return mTiles[(int)std::abs(offset.x)][(int)std::abs(offset.y)][(int)std::abs(offset.z)];
	}

	void Chunk::chunkUpdated()
	{
		auto* renderQueue = ViperCraft::GetInstance()->getRenderQueue();
		renderQueue->resetModels(mRenderBuffer);
		renderQueue->resetModels(mTransparentRenderBuffer);

		glm::vec3 position = mPosition;
		for (auto& yz : mTiles)
		{
			for (auto& z : yz)
			{
				for (auto tile : z)
				{
					if (tile && tile->getName() != "air") // maybe add tile ids or something to check against here
					{
						if (tile->isLiquid())
							tile->draw(mTransparentRenderBuffer, position, renderQueue);
						else
							tile->draw(mRenderBuffer, position, renderQueue);
					}
					position.z += 1;
				}
				position.z = mPosition.z;
				position.y += 1;
			}
			position.y = mPosition.y;
			position.x += 1;
		}

		renderQueue->bindModels(mRenderBuffer);
		renderQueue->bindModels(mTransparentRenderBuffer);
	}
}