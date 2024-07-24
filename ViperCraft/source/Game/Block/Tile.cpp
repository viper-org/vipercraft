#include <Game/Block/Tile.h>

#include <ViperCraft/ViperCraft.h>

#include <unordered_map>

namespace ViperCraft
{
	constinit int blockid = 0;
	std::unordered_map<std::string_view, Tile> tiles = {
		{ "air", Tile({-1,-1}, Block::AIR)},

		{ "cobblestone", Tile({
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
			ViperGL::TextureCoords{0,0},
		}, Block::COBBLESTONE)},

		{ "dirt", Tile({
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{1,0},
		}, Block::DIRT)},

		{ "grass_block", Tile({
			ViperGL::TextureCoords{1,0},
			ViperGL::TextureCoords{3,0},
			ViperGL::TextureCoords{2,0},
			ViperGL::TextureCoords{2,0},
			ViperGL::TextureCoords{2,0},
			ViperGL::TextureCoords{2,0},
		}, Block::GRASS_BLOCK)},

		{ "stone", Tile({
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
			ViperGL::TextureCoords{0,1},
		}, Block::STONE)},

		{ "water", Tile({
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
			ViperGL::TextureCoords{1,1},
		}, Block::WATER)},

		{ "sand", Tile({
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
			ViperGL::TextureCoords{2,1},
		}, Block::SAND)},

		{ "wood", Tile({
			ViperGL::TextureCoords{0,2},
			ViperGL::TextureCoords{0,2},
			ViperGL::TextureCoords{1,2},
			ViperGL::TextureCoords{1,2},
			ViperGL::TextureCoords{1,2},
			ViperGL::TextureCoords{1,2},
		}, Block::WOOD)},

		{ "leaves", Tile({
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
			ViperGL::TextureCoords{2,2},
		}, Block::LEAVES)},

		{ "gravel", Tile({
			ViperGL::TextureCoords{3,1},
			ViperGL::TextureCoords{3,1},
			ViperGL::TextureCoords{3,1},
			ViperGL::TextureCoords{3,1},
			ViperGL::TextureCoords{3,1},
			ViperGL::TextureCoords{3,1},
		}, Block::GRAVEL)},

		{ "coal_ore", Tile({
			ViperGL::TextureCoords{0,3},
			ViperGL::TextureCoords{0,3},
			ViperGL::TextureCoords{0,3},
			ViperGL::TextureCoords{0,3},
			ViperGL::TextureCoords{0,3},
			ViperGL::TextureCoords{0,3},
		}, Block::COAL_ORE)},

		{ "glass", Tile({
			ViperGL::TextureCoords{1,3},
			ViperGL::TextureCoords{1,3},
			ViperGL::TextureCoords{1,3},
			ViperGL::TextureCoords{1,3},
			ViperGL::TextureCoords{1,3},
			ViperGL::TextureCoords{1,3},
		}, Block::GLASS)},

		{ "iron_ore", Tile({
			ViperGL::TextureCoords{2,3},
			ViperGL::TextureCoords{2,3},
			ViperGL::TextureCoords{2,3},
			ViperGL::TextureCoords{2,3},
			ViperGL::TextureCoords{2,3},
			ViperGL::TextureCoords{2,3},
		}, Block::IRON_ORE)},
	};

	Tile::Tile()
		: mFaceTextures()
		, mId(Block::AIR)
	{
	}

	Tile::Tile(std::array<ViperGL::TextureCoords, 6> faceTextures, Block id)
		: mFaceTextures(faceTextures)
		, mId(id)
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
			if (position.y + facing >= 0) // always generate the very bottom of the world
			{
				auto tile = world->getTile(position + glm::vec3(0, facing, 0));
				if (tile && (!tile->isTransparent() || (isLiquid() && tile->isLiquid()))) continue;
			}

			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-3)] = position + glm::vec3(0, height * i, 1);
			corners[abs((i*3)-2)] = position + glm::vec3(1, height * i, 1);
			corners[abs((i*3)-1)] = position + glm::vec3(1, height * i, 0);
			corners[abs((i*3)-0)] = position + glm::vec3(0, height * i, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i].x, mFaceTextures[i].y), 1.f, isLiquid()?0.6f:1.f);
		}
		// left and right
		for (int i = 0; i < 2; ++i)
		{
			auto facing = -1 + 2 * i;
			auto tile = world->getTile(position + glm::vec3(facing, 0, 0));
			if (tile && (!tile->isTransparent() || (isLiquid() && tile->isLiquid()))) continue;

			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-2)] = position + glm::vec3(i, 0, 1);
			corners[abs((i*3)-3)] = position + glm::vec3(i, height, 1);
			corners[abs((i*3)-0)] = position + glm::vec3(i, height, 0);
			corners[abs((i*3)-1)] = position + glm::vec3(i, 0, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i+2].x, mFaceTextures[i+2].y), .6f, isLiquid() ? 0.6f : 1.f);
		}
		// front and back
		for (int i = 0; i < 2; ++i)
		{
			auto facing = -1 + 2 * i;
			auto tile = world->getTile(position + glm::vec3(0, 0, facing));
			if (tile && (!tile->isTransparent() || (isLiquid() && tile->isLiquid()))) continue;

			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-3)] = position + glm::vec3(0, height, i);
			corners[abs((i*3)-0)] = position + glm::vec3(1, height, i);
			corners[abs((i*3)-1)] = position + glm::vec3(1, 0, i);
			corners[abs((i*3)-2)] = position + glm::vec3(0, 0, i);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i+4].x, mFaceTextures[i+4].y), .8f, isLiquid() ? 0.6f : 1.f);
		}
	}

	void Tile::update(glm::vec3 position)
	{
		if (mId == Block::WATER)
		{
			auto surroundings = Tile::GetFlowableSurroundings(position);
			for (auto& pos : surroundings)
			{
				auto chunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(pos);
				if (!chunk) continue;
				auto& tile = chunk->getTile(pos);
				if (!tile)
				{
					tile = Tile::GetTile("water");
					tile->update(pos);
				}
			}
		}
	}

	Block Tile::getId() const
	{
		return mId;
	}

	bool Tile::isTransparent() const
	{
		return mId == Block::AIR || mId == Block::WATER || mId == Block::GLASS;
	}

	bool Tile::isSolidTile() const
	{
		return mId != Block::AIR && mId != Block::WATER;
	}

	bool Tile::isLiquid() const
	{
		return mId == Block::WATER;
	}

	Tile* Tile::GetTile(std::string_view name)
	{
		return &tiles[name];
	}

	Tile* Tile::GetTile(Block id)
	{
		auto it = std::find_if(tiles.begin(), tiles.end(), [id](const auto& tile) {
			return tile.second.getId() == id;
			});
		if (it == tiles.end()) return nullptr;
		return &it->second;
	}

	std::array<glm::vec3, 6> Tile::GetSurroundings(glm::vec3 position)
	{
		return std::array<glm::vec3, 6>{
			position + glm::vec3(1, 0, 0),
			position - glm::vec3(1, 0, 0),
			position + glm::vec3(0, 1, 0),
			position - glm::vec3(0, 1, 0),
			position + glm::vec3(0, 0, 1),
			position - glm::vec3(0, 0, 1),
		};
	}

	std::array<glm::vec3, 5> Tile::GetFlowableSurroundings(glm::vec3 position)
	{
		return std::array<glm::vec3, 5>{
			position + glm::vec3(1, 0, 0),
			position - glm::vec3(1, 0, 0),
			position - glm::vec3(0, 1, 0),
			position + glm::vec3(0, 0, 1),
			position - glm::vec3(0, 0, 1),
		};
	}

	std::array<glm::vec3, 4> Tile::GetOrthoSurroundings(glm::vec3 position)
	{
		return std::array<glm::vec3, 4>{
			position + glm::vec3(1, 0, 0),
			position - glm::vec3(1, 0, 0),
			position + glm::vec3(0, 0, 1),
			position - glm::vec3(0, 0, 1),
		};
	}
}