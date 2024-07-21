#include <Game/World/World.h>

#include <ViperCraft/ViperCraft.h>

namespace ViperCraft
{
	World::World()
	{
	}

	Chunk* World::getPositionChunk(glm::vec3 position)
	{
		glm::vec3 offset = mLoadedChunks[0][0].mPosition - position;
		
		offset.x /= 16;
		offset.z /= 16;

		return &mLoadedChunks[(int)abs(offset.x)][(int)abs(offset.z)];
	}

	void World::render()
	{
		ViperCraft::GetInstance()->getRenderQueue()->draw();
	}


	void World::Generate(World& world)
	{
		constexpr int WORLD_SIZE = 4;
		world.mLoadedChunks.reserve(WORLD_SIZE);
		glm::vec3 chunkPosition = glm::vec3(0.f);
		for (auto i = 0; i < WORLD_SIZE; ++i)
		{
			world.mLoadedChunks.push_back(std::vector<Chunk>(WORLD_SIZE));
			for (auto& chunk : world.mLoadedChunks.back())
			{
				chunk.beginRendering();
				chunk.mPosition = chunkPosition;
				chunkPosition.z += 16;
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 16; ++j)
					{
						chunk.getTile(glm::vec3(chunk.mPosition.x + i, 2, chunk.mPosition.z + j)) = Tile::GetTile("grass_block");
						chunk.getTile(glm::vec3(chunk.mPosition.x + i, 1, chunk.mPosition.z + j)) = Tile::GetTile("dirt");
						chunk.getTile(glm::vec3(chunk.mPosition.x + i, 0, chunk.mPosition.z + j)) = Tile::GetTile("cobblestone");
					}
				}
				chunk.chunkUpdated();
			}
			chunkPosition.x += 16;
			chunkPosition.z = 0;
		}
	}
}