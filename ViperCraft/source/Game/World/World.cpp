#include <Game/World/World.h>

#include <ViperCraft/ViperCraft.h>

#include <stb_perlin/stb_perlin.h>

#include <algorithm>
#include <iostream>

namespace ViperCraft
{
	World::World()
	{
	}

	Tile* World::getTile(glm::vec3 position)
	{
		Chunk* chunk = getPositionChunk(position);
		if (!chunk) return nullptr;
		return chunk->getTile(position);
	}

	Chunk* World::getPositionChunk(glm::vec3 position)
	{
		glm::vec3 offset = mLoadedChunks[0][0].mPosition - position;
		if (position.x < mLoadedChunks[0][0].mPosition.x) return nullptr;
		if (position.z < mLoadedChunks[0][0].mPosition.z) return nullptr;
		
		offset.x /= 16;
		offset.z /= 16;
		if (abs(offset.x) >= mLoadedChunks.size())    return nullptr;
		if (abs(offset.z) >= mLoadedChunks[0].size()) return nullptr;

		return &mLoadedChunks[(int)abs(offset.x)][(int)abs(offset.z)];
	}

	void World::render()
	{
		ViperCraft::GetInstance()->getRenderQueue()->prepareDraw();

		// we can probably do all of this only when the player moves but for now its fine
		auto playerPos = ViperCraft::GetInstance()->getPlayer()->getPosition();
		std::vector<std::vector<Chunk*> > sortedChunks;
		for (auto& chunks : mLoadedChunks)
		{
			sortedChunks.push_back(std::vector<Chunk*>());
			for (auto& chunk : chunks)
			{
				sortedChunks.back().push_back(&chunk);
			}
		}

		std::sort(sortedChunks.begin(), sortedChunks.end(), [this, &playerPos](const std::vector<Chunk*>& a, const std::vector<Chunk*>& b) {
			return (glm::length(a.front()->getPosition().x - playerPos.x)) > (glm::length(b.front()->getPosition().x - playerPos.x));
		});
		for (auto& chunks : sortedChunks)
		{
			std::sort(chunks.begin(), chunks.end(), [this, &playerPos](Chunk* a, Chunk* b) {
				return (glm::length(a->getPosition().z - playerPos.z)) > (glm::length(b->getPosition().z - playerPos.z));
			});
		}

		for (auto& chunks : sortedChunks)
		{
			for (auto& chunk : chunks)
			{
				chunk->draw();
			}
		}
		mSky.draw();
	}


	constexpr int WORLD_SIZE = 2;
	void World::Generate(World& world, unsigned long long seed)
	{
		constexpr float WORLDGEN_INTENSITY = 5.f;
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
						auto height = (
							stb_perlin_noise3_seed((chunk.mPosition.x + i) / 16, (chunk.mPosition.z + j) / 16, .2f, 0, 0, 0, seed) +
							stb_perlin_noise3_seed((chunk.mPosition.x + i) / 16, (chunk.mPosition.z + j) / 16, .9f, 0, 0, 0, seed) -
							stb_perlin_noise3_seed((chunk.mPosition.x + i) / 16, (chunk.mPosition.z + j) / 16, .7f, 0, 0, 0, seed)
							) * WORLDGEN_INTENSITY + 60;
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
						GenerateTree(world, chunk, height, position);
					}
				}
				delete[] chunk.mHeights;
			}
			chunkPosition.x += 16;
			chunkPosition.z = 0;
		}

		GenerateCaves(world, seed);

		ViperCraft::GetInstance()->setPlayerSpawn(playerSpawn);
		for (auto& chunks : world.mLoadedChunks)
		{
			for (auto& chunk : chunks)
			{
				chunk.chunkUpdated();
			}
		}

		world.mSky.addClouds(seed, glm::vec2(WORLD_SIZE * 16));
	}

	void World::GenerateCaves(World& world, unsigned long long seed)
	{
		for (float x = 0; x < WORLD_SIZE * 16; ++x)
		{
			for (float y = 0; y < 256; ++y)
			{
				for (float z = 0; z < WORLD_SIZE * 16; ++z)
				{
					auto noise = (
						stb_perlin_noise3_seed(x / 16, y / 16, z / 16, 0, 0, 0, seed) *
						stb_perlin_noise3_seed(x / 8, y / 8, z / 8, 0, 0, 0, seed)
						);
					if (noise >= 0.1f)
					{
						auto chunk = world.getPositionChunk(glm::vec3(x, y, z));
						chunk->getTile(glm::vec3(x, y, z)) = nullptr; // air
					}
					else if (noise >= 0.0997f || noise <= -0.14f)
					{
						if (y < 57)
						{
							auto chunk = world.getPositionChunk(glm::vec3(x, y, z));
							chunk->getTile(glm::vec3(x, y, z)) = Tile::GetTile("coal_ore");
						}
					}
				}
			}
		}
	}


	void World::GenerateWater(Chunk& chunk, float height, glm::vec2 position)
	{
		constexpr float WATER_HEIGHT = 59;
		if (height < WATER_HEIGHT)
		{
			bool generateWater = !(height >= WATER_HEIGHT - .6);
			std::string block = generateWater ? "water" : "sand";
			for (int y = height; y < WATER_HEIGHT; ++y)
			{
				chunk.getTile(glm::vec3(position.x, y, position.y)) = Tile::GetTile(block);
			}
			if (generateWater)
				chunk.getTile(glm::vec3(position.x, height-1, position.y)) = Tile::GetTile("gravel");
		}
	}

	void World::GenerateTree(World& world, Chunk& chunk, float height, glm::vec2 position)
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
		constexpr float TREE_LIKELIHOOD = 0.999;

		if (rand() >= RAND_MAX * TREE_LIKELIHOOD)
		{
			for (const auto& surrounding : surroundings)
			{
				auto currChunk = world.getPositionChunk(glm::vec3(position.x, height + 1, position.y) + surrounding);
				if (!currChunk) continue;
				if (currChunk->getTile(glm::vec3(position.x, height + 1, position.y) + surrounding) != nullptr) return;
			}
			PlaceTree(world, glm::vec3(position.x, height + 1, position.y));
		}
	}

	void World::PlaceTree(World& world, glm::vec3 position)
	{
		constexpr std::array<glm::vec3, 8> immediate_surroundings = {
			// immediate surroundings
			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, -1),
			glm::vec3(0, 0, -1),
			glm::vec3(-1, 0, -1),
		};
		constexpr std::array<glm::vec3, 5> plus = {
			glm::vec3(0, 0, 0),
			glm::vec3(-1, 0, 0),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, -1),
		};
		constexpr std::array<glm::vec3, 12> second_surroundings = {
			glm::vec3(0, 0, -2),
			glm::vec3(1, 0, -2),
			glm::vec3(2, 0, -1),
			glm::vec3(2, 0, 0),
			glm::vec3(2, 0, 1),
			glm::vec3(1, 0, 2),
			glm::vec3(0, 0, 2),
			glm::vec3(-1, 0, 2),
			glm::vec3(-2, 0, 1),
			glm::vec3(-2, 0, 0),
			glm::vec3(-2, 0, -1),
			glm::vec3(-1, 0, -2)
		};
		int tree_height = (rand() % 2 == 0) ? 7 : 6;

		auto trunkChunk = world.getPositionChunk(position);
		for (int y = 0; y < tree_height; ++y)
		{
			trunkChunk->getTile(glm::vec3(position.x, position.y + y, position.z)) = Tile::GetTile("wood");
		}

		// draw the leaves directly around the log
		for (int y = 3; y < tree_height-1; ++y)
		{
			for (const auto& leaf : immediate_surroundings)
			{
				auto currChunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(glm::vec3(position.x, position.y + y, position.z) + leaf);
				if (!currChunk) continue;
				currChunk->getTile(glm::vec3(position.x, position.y + y, position.z) + leaf) = Tile::GetTile("leaves");
			}
		}

		// draw the plus on top
		for (const auto& leaf : plus)
		{
			auto currChunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(glm::vec3(position.x, position.y + tree_height - 1, position.z) + leaf);
			if (!currChunk) continue;
			currChunk->getTile(glm::vec3(position.x, position.y + tree_height - 1, position.z) + leaf) = Tile::GetTile("leaves");
		}

		// draw the last layer of leaves
		for (int y = tree_height-4; y < tree_height-2; ++y)
		{
			for (const auto& leaf : second_surroundings)
			{
				auto currChunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(glm::vec3(position.x, position.y + y, position.z) + leaf);
				if (!currChunk) continue;
				currChunk->getTile(glm::vec3(position.x, position.y + y, position.z) + leaf) = Tile::GetTile("leaves");
			}
		}
	}
}