#include <Game/Block/Tile.h>

#include <unordered_map>

namespace ViperCraft
{
	std::unordered_map<std::string_view, Tile> tiles = {
		{ "air", Tile(-1, "air", "air")},
		{ "cobblestone", Tile(-1, "cobblestone", "cobblestone")},
	};

	Tile::Tile()
		: mRenderableId(-1)
	{
	}

	Tile::Tile(int renderableId, std::string_view textureId, std::string name)
		: mRenderableId(renderableId)
		, mTextureId(textureId)
		, mName(std::move(name))
	{
	}

	int Tile::getRenderableId() const
	{
		return mRenderableId;
	}

	Tile* Tile::GetTile(std::string_view name)
	{
		return &tiles[name];
	}

	void Tile::BuildRenderables(ViperGL::RenderQueue& renderQueue)
	{
		for (auto& [_, tile] : tiles)
		{
			if (tile.mName != "air")
				tile.mRenderableId = renderQueue.push(ViperGL::Voxel(tile.mTextureId));
		}
	}
}