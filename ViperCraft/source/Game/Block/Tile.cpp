#include <Game/Block/Tile.h>

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
		// TODO: Find visible quads and render those only

		// top and bottom
		for (int i = 0; i < 2; ++i)
		{
			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-3)] = position + glm::vec3(0, i, 1);
			corners[abs((i*3)-2)] = position + glm::vec3(1, i, 1);
			corners[abs((i*3)-1)] = position + glm::vec3(1, i, 0);
			corners[abs((i*3)-0)] = position + glm::vec3(0, i, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i].x, mFaceTextures[i].y), 1.f);
		}
		// left and right
		for (int i = 0; i < 2; ++i)
		{
			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-2)] = position + glm::vec3(i, 0, 1);
			corners[abs((i*3)-3)] = position + glm::vec3(i, 1, 1);
			corners[abs((i*3)-0)] = position + glm::vec3(i, 1, 0);
			corners[abs((i*3)-1)] = position + glm::vec3(i, 0, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mFaceTextures[i+2].x, mFaceTextures[i+2].y), .6f);
		}
		// front and back
		for (int i = 0; i < 2; ++i)
		{
			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-3)] = position + glm::vec3(0, 1, i);
			corners[abs((i*3)-0)] = position + glm::vec3(1, 1, i);
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
		return mName != "air"; // TODO: Store this properly(or move the whole thing to a proper collision system)
	}

	Tile* Tile::GetTile(std::string_view name)
	{
		return &tiles[name];
	}
}