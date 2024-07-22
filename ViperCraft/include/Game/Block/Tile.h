#pragma once

#include <ViperGL/Render/RenderQueue.h>

#include <string>

namespace ViperCraft
{
	class Tile
	{
	public:
		Tile();
		Tile(std::array<ViperGL::TextureCoords, 6> faceTextures, std::string name);

		void draw(int renderBuffer, glm::vec3 position, ViperGL::RenderQueue* renderQueue);

		std::string_view getName() const;
		bool isSolidTile() const;
		bool isLiquid() const;

		static Tile* GetTile(std::string_view name);

	private:
		std::array<ViperGL::TextureCoords, 6> mFaceTextures;
		std::string mName;
	};
}