#pragma once

#include <ViperGL/Render/RenderQueue.h>

#include <string>

namespace ViperCraft
{
	enum class Block
	{
		AIR=0,
		COBBLESTONE,
		DIRT,
		GRASS_BLOCK,
		STONE,
		WATER,
		SAND,
		WOOD,
		LEAVES,
		GRAVEL,
		COAL_ORE,
		GLASS,
		IRON_ORE
	};

	class Tile
	{
	public:
		Tile();
		Tile(std::array<ViperGL::TextureCoords, 6> faceTextures, Block id);

		void draw(int renderBuffer, glm::vec3 position, ViperGL::RenderQueue* renderQueue);
		void update(glm::vec3 position);

		Block getId() const;

		bool isTransparent() const;
		bool isSolidTile() const;
		bool isLiquid() const;

		static Tile* GetTile(std::string_view name);
		static Tile* GetTile(Block id);
		static std::array<glm::vec3, 6> GetSurroundings(glm::vec3 position);
		static std::array<glm::vec3, 5> GetFlowableSurroundings(glm::vec3 position);
		static std::array<glm::vec3, 4> GetOrthoSurroundings(glm::vec3 position);

	private:
		std::array<ViperGL::TextureCoords, 6> mFaceTextures;
		Block mId;
	};
}