#pragma once

#include <ViperGL/Render/RenderQueue.h>

#include <string>

namespace ViperCraft
{
	class Tile
	{
	public:
		Tile();
		Tile(int renderableId, std::string_view textureId, std::string name);

		int getRenderableId() const;

		static Tile* GetTile(std::string_view name);
		static void BuildRenderables(ViperGL::RenderQueue& renderQueue);

	private:
		int mRenderableId;
		std::string_view mTextureId;
		std::string mName;
	};
}