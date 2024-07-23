#pragma once

#include <Game/Block/Tile.h>

#include <ViperGL/Render/RenderQueue.h>

#include <glm/vec3.hpp>

namespace ViperCraft
{
	class Chunk
	{
	friend class ViperCraft;
	friend class World;
	public:
		Chunk();
		Chunk(glm::vec3 position);

		void beginRendering();
		void drawOpaque();
		void drawTransparent();

		void chunkUpdated();

		glm::vec3 getPosition();
		Tile*& getTile(glm::vec3 position);
		Tile*& getTileOffset(glm::vec3 offset);

	private:
		Tile* mTiles[16][256][16]; // x, y, z
		float* mHeights;
		glm::vec3 mPosition; // bottom left back side

		int mRenderBuffer;
		int mTransparentRenderBuffer;
	};
}