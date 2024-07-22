#pragma once

#include <Game/Block/Chunk.h>

#include <memory>

namespace ViperCraft
{
	class World
	{
	public:
		World();

		Chunk* getPositionChunk(glm::vec3 position);

		void render();

		static void Generate(World& world, unsigned long long seed);

	private:
		std::vector<std::vector<Chunk> > mLoadedChunks; // x, z - only chunks that are to be rendered, other chunks are loaded when needed

		static void GenerateWater(Chunk& chunk, float height, glm::vec2 position);
		static void GenerateTree(World& world, Chunk& chunk, float height, glm::vec2 position);
		static void PlaceTree(World& world, glm::vec3 position);
	};
}