#include <Game/Block/Tile.h>

#include <unordered_map>

namespace ViperCraft
{
	std::unordered_map<std::string_view, Tile> tiles = {
		{ "air", Tile({-1,-1}, "air")},
		{ "cobblestone", Tile({0,0}, "cobblestone")},
		{ "dirt", Tile({1,0}, "dirt")},
	};

	Tile::Tile()
		: mTexture({-1, -1})
	{
	}

	Tile::Tile(ViperGL::TextureCoords texture, std::string name)
		: mTexture(texture)
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
			renderQueue->quad(renderBuffer, corners, glm::vec2(mTexture.x, mTexture.y));
		}
		// left and right
		for (int i = 0; i < 2; ++i)
		{
			std::array<glm::vec3, 4> corners;
			corners[abs((i*3)-0)] = position + glm::vec3(i, 0, 1);
			corners[abs((i*3)-1)] = position + glm::vec3(i, 1, 1);
			corners[abs((i*3)-2)] = position + glm::vec3(i, 1, 0);
			corners[abs((i*3)-3)] = position + glm::vec3(i, 0, 0);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mTexture.x, mTexture.y));
		}
		// front and back
		for (int i = 0; i < 2; ++i)
		{
			std::array<glm::vec3, 4> corners;
			corners[abs((i * 3) - 0)] = position + glm::vec3(0, 1, i);
			corners[abs((i * 3) - 1)] = position + glm::vec3(1, 1, i);
			corners[abs((i * 3) - 2)] = position + glm::vec3(1, 0, i);
			corners[abs((i * 3) - 3)] = position + glm::vec3(0, 0, i);
			renderQueue->quad(renderBuffer, corners, glm::vec2(mTexture.x, mTexture.y));
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