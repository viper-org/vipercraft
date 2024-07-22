#include <Game/World/World.h>

#include <ViperCraft/ViperCraft.h>

#include <stb_perlin/stb_perlin.h>

#include <iostream>

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
		if (abs(offset.x) >= mLoadedChunks.size())    return nullptr;
		if (abs(offset.z) >= mLoadedChunks[0].size()) return nullptr;

		return &mLoadedChunks[(int)abs(offset.x)][(int)abs(offset.z)];
	}

	void World::render()
	{
		ViperCraft::GetInstance()->getRenderQueue()->draw();
	}


	void World::Generate(World& world, unsigned long long seed)
	{
		constexpr int WORLD_SIZE = 8;
		constexpr float WORLDGEN_INTENSITY = 7.5f;
		constexpr float center = float(WORLD_SIZE * 16) / 2;

		srand(seed);

		glm::vec3 playerSpawn = glm::vec3(center, 0, center);

		world.mLoadedChunks.reserve(WORLD_SIZE);
		glm::vec3 chunkPosition = glm::vec3(0.f);
		// Basic worldgen
		for (auto i = 0; i < WORLD_SIZE; ++i)
		{
			world.mLoadedChunks.push_back(std::vector<Chunk>(WORLD_SIZE));
			for (auto& chunk : world.mLoadedChunks.back())
			{
				chunk.beginRendering();
				chunk.mPosition = chunkPosition;
				chunkPosition.z += 16;
				chunk.mHeights = new float[256];
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 16; ++j)
					{
						auto height = floor((
							stb_perlin_noise3_seed((chunk.mPosition.x + i) / 16, (chunk.mPosition.z + j) / 16, .2f, 0, 0, 0, seed) +
							stb_perlin_noise3_seed((chunk.mPosition.x + i) / 16, (chunk.mPosition.z + j) / 16, .5f, 0, 0, 0, seed) -
							stb_perlin_noise3_seed((chunk.mPosition.x + i) / 16, (chunk.mPosition.z + j) / 16, .7f, 0, 0, 0, seed) 
							) * WORLDGEN_INTENSITY + 60);
						chunk.mHeights[i + j * 16] = height;

						chunk.getTile(glm::vec3(chunk.mPosition.x + i, height, chunk.mPosition.z + j)) = Tile::GetTile("grass_block");
						for (int y = 1; y < 3; ++y)
						{
							if (height - y < 0) break;
							chunk.getTile(glm::vec3(chunk.mPosition.x + i, height - y, chunk.mPosition.z + j)) = Tile::GetTile("dirt");
						}
						for (int y = height-3; y >= 0; --y)
						{
							chunk.getTile(glm::vec3(chunk.mPosition.x + i, y, chunk.mPosition.z + j)) = Tile::GetTile("stone");
						}
						if (chunk.mPosition.x + i == center && chunk.mPosition.z + j == center)
							playerSpawn.y = height + 1.f;

						glm::vec2 position = glm::vec2(chunk.mPosition.x + i, chunk.mPosition.z + j);
						GenerateWater(chunk, height, position);
					}
				}
			}
			chunkPosition.x += 16;
			chunkPosition.z = 0;
		}

		// Fauna
		for (auto i = 0; i < WORLD_SIZE; ++i)
		{
			for (auto& chunk : world.mLoadedChunks[i])
			{
				chunkPosition.z += 16;
				for (int i = 0; i < 16; ++i)
				{
					for (int j = 0; j < 16; ++j)
					{
						// probably shouldnt be regenerating this but oh well
						auto height = chunk.mHeights[i + j * 16];
						glm::vec2 position = glm::vec2(chunk.mPosition.x + i, chunk.mPosition.z + j);
						GenerateTree(chunk, height, position);
					}
				}
				delete[] chunk.mHeights;
			}
			chunkPosition.x += 16;
			chunkPosition.z = 0;
		}

		ViperCraft::GetInstance()->setPlayerSpawn(playerSpawn);
		for (auto& chunks : world.mLoadedChunks)
		{
			for (auto& chunk : chunks)
			{
				chunk.chunkUpdated();
			}
		}
	}


	void World::GenerateWater(Chunk& chunk, float height, glm::vec2 position)
	{
		if (height < 60)
		{
			std::string block = (height >= 59.f) ? "sand" : "water";
			for (int y = height; y < 60; ++y)
			{
				chunk.getTile(glm::vec3(position.x, y, position.y)) = Tile::GetTile(block);
			}
		}
	}

	void World::GenerateTree(Chunk& chunk, float height, glm::vec2 position)
	{
		if (chunk.getTile(glm::vec3(position.x, height, position.y))->getName() != "grass_block") return; // trees can only be generated on grass
		constexpr std::array<glm::vec3, 8> surroundings = {
			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, -1),
			glm::vec3(0, 0, -1),
			glm::vec3(-1, 0, -1),
		};

		if (rand() >= RAND_MAX * 0.976f) // put a tree at this coordinate
		{
			for (const auto& surrounding : surroundings)
			{
				auto currChunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(glm::vec3(position.x, height + 1, position.y) + surrounding);
				if (!currChunk) continue;
				if (currChunk->getTile(glm::vec3(position.x, height + 1, position.y) + surrounding) != nullptr) return;
			}

			for (int y = 1; y < 7; ++y)
			{
				chunk.getTile(glm::vec3(position.x, height + y, position.y)) = Tile::GetTile("wood");
			}
			for (int y = 3; y < 7; ++y)
			{
				for (const auto& surrounding : surroundings)
				{
					auto currChunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(glm::vec3(position.x, height + y, position.y) + surrounding);
					if (!currChunk) continue;
					currChunk->getTile(glm::vec3(position.x, height + y, position.y) + surrounding) = Tile::GetTile("leaves");
				}
			}
		}
	}
}