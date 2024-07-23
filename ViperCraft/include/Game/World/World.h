#pragma once

#include <Game/World/Sky.h>

#include <Game/Block/Chunk.h>

#include <memory>

namespace ViperCraft
{
	class World
	{
	public:
		World();

		Tile* getTile(glm::vec3 position);
		Chunk* getPositionChunk(glm::vec3 position);
		glm::vec3 getSpawnPoint();

		void clear();
		void saveToFile(std::string_view path);
		static void LoadFromFile(World& world, std::string_view path);

		void render();

		static void Generate(World& world, unsigned long long seed);

	private:
		std::vector<std::vector<Chunk> > mLoadedChunks; // x, z - only chunks that are to be rendered, other chunks are loaded when needed
		Sky mSky;
		glm::vec3 mSpawnPoint;
		unsigned long long mCreatedAt;

		static void GenerateCaves(World& world, unsigned long long seed);
		static void GenerateWater(Chunk& chunk, float height, glm::vec2 position);
		static void GenerateTree(World& world, Chunk& chunk, float height, glm::vec2 position);
		static void PlaceTree(World& world, glm::vec3 position);
	};
}