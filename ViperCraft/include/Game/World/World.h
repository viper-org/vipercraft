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

		static void Generate(World& world); // checkered flat 16x16 for now only

	private:
		std::vector<std::vector<Chunk> > mLoadedChunks; // x, z - only chunks that are to be rendered, other chunks are loaded when needed
	};
}