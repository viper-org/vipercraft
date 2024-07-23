#pragma once

#include <ViperGL/Render/RenderQueue.h>

#include <string>

namespace ViperCraft
{
	class Tile
	{
	public:
		Tile();
		Tile(std::array<ViperGL::TextureCoords, 6> faceTextures, std::string name, int id);

		void draw(int renderBuffer, glm::vec3 position, ViperGL::RenderQueue* renderQueue);
		void update(glm::vec3 position);

		std::string_view getName() const;
		int getId() const;

		bool isSolidTile() const;
		bool isLiquid() const;

		static Tile* GetTile(std::string_view name);
		static Tile* GetTile(int id);
		static std::array<glm::vec3, 6> GetSurroundings(glm::vec3 position);
		static std::array<glm::vec3, 5> GetFlowableSurroundings(glm::vec3 position);
		static std::array<glm::vec3, 4> GetOrthoSurroundings(glm::vec3 position);

	private:
		std::array<ViperGL::TextureCoords, 6> mFaceTextures;
		std::string mName;
		int mId;
	};
}