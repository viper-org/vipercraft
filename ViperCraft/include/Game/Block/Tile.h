#pragma once

#include <ViperGL/Render/RenderQueue.h>

#include <string>

namespace ViperCraft
{
	class Tile
	{
	public:
		Tile();
		Tile(ViperGL::TextureCoords texture, std::string name);

		void draw(int renderBuffer, glm::vec3 position, ViperGL::RenderQueue* renderQueue);

		std::string_view getName() const;

		static Tile* GetTile(std::string_view name);

	private:
		ViperGL::TextureCoords mTexture;
		std::string mName;
	};
}