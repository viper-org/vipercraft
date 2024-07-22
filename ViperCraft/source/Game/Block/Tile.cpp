#include <Game/Block/Tile.h>

#include <ViperCraft/ViperCraft.h>

#include <unordered_map>

namespace ViperCraft
{
	std::unordered_map<std::string_view, Tile> tiles = {
		{ "air", Tile({-1,-1}, "air")},

		{ "cobblestone", Tile({
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
		}, "cobblestone")},

		{ "dirt", Tile({
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
		}, "dirt")},

		{ "grass_block", Tile({
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{3,0},
			ViperGL::TextureCoords{2,0},
			ViperGL::TextureCoords{2,0},
			ViperGL::TextureCoords{2,0},
			ViperGL::TextureCoords{2,0},
		}, "grass_block")},

		{ "stone", Tile({
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
		}, "stone")},

		{ "water", Tile({
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
		}, "water")},

		{ "sand", Tile({
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
		}, "sand")},

		{ "wood", Tile({
			ViperGL::TextureCoords{0,2},
			ViperGL::TextureCoords{0,2},
			ViperGL::TextureCoords{1,2},
			ViperGL::TextureCoords{1,2},
			ViperGL::TextureCoords{1,2},
			ViperGL::TextureCoords{1,2},
		}, "wood")},

		{ "leaves", Tile({
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
		}, "leaves")},
	};

	Tile::Tile()
		: mFaceTextures()
	{
	}

	Tile::Tile(std::array<ViperGL::TextureCoords, 6> faceTextures, std::string name)
		: mFaceTextures(faceTextures)
		, mName(std::move(name))
	{
	}

	void Tile::draw(int renderBuffer, glm::vec3 position, ViperGL::RenderQueue* renderQueue)
	{
		auto world = ViperCraft::GetInstance()->getWorld();
		auto height = isLiquid() ? 0.9f : 1.f;
		
		// top and bottom
		for (int i = 0; i < 2; ++i)
		{
			auto facing = -1 + 2 * i;
			auto chunk = world->getPositionChunk(position + glm::vec3(0, facing, 0));
			if (chunk)
			{
				auto tile = chunk->getTile(position + glm::vec3(0, facing, 0));
				if (tile && tile->isSolidTile()) continue;
			}

			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-3)] = position + glm::vec3(0, height * i, 1);
			corners[abs((i*3)-2)] = position + glm::vec3(1, height * i, 1);
			corners[abs((i*3)-1)] = position + glm::vec3(1, height * i, 0);
			corners[abs((i*3)-0)] = position + glm::vec3(0, height * i, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i].x, mFaceTextures[i].y), 1.f);
		}
		// left and right
		for (int i = 0; i < 2; ++i)
		{
			auto facing = -1 + 2 * i;
			auto chunk = world->getPositionChunk(position + glm::vec3(facing, 0, 0));
			if (chunk)
			{
				auto tile = chunk->getTile(position + glm::vec3(facing, 0, 0));
				if (tile && tile->isSolidTile()) continue;
			}

			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-2)] = position + glm::vec3(i, 0, 1);
			corners[abs((i*3)-3)] = position + glm::vec3(i, height, 1);
			corners[abs((i*3)-0)] = position + glm::vec3(i, height, 0);
			corners[abs((i*3)-1)] = position + glm::vec3(i, 0, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i+2].x, mFaceTextures[i+2].y), .6f);
		}
		// front and back
		for (int i = 0; i < 2; ++i)
		{
			auto facing = -1 + 2 * i;
			auto chunk = world->getPositionChunk(position + glm::vec3(0, 0, facing));
			if (chunk)
			{
				auto tile = chunk->getTile(position + glm::vec3(0, 0, facing));
				if (tile && tile->isSolidTile()) continue;
			}

			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-3)] = position + glm::vec3(0, height, i);
			corners[abs((i*3)-0)] = position + glm::vec3(1, height, i);
			corners[abs((i*3)-1)] = position + glm::vec3(1, 0, i);
			corners[abs((i*3)-2)] = position + glm::vec3(0, 0, i);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i+4].x, mFaceTextures[i+4].y), .8f);
		}
	}

	std::string_view Tile::getName() const
	{
		return mName;
	}

	bool Tile::isSolidTile() const
	{
		return mName != "air" && mName != "water";
	}

	bool Tile::isLiquid() const
	{
		return mName == "water";
	}

	Tile* Tile::GetTile(std::string_view name)
	{
		return &tiles[name];
	}
}