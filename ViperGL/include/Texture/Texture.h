#pragma once

#include <glm/vec2.hpp>

#include <string>

namespace ViperGL
{
	class TextureAtlas
	{
	public:
		TextureAtlas(const std::string& name);

		void bind();

		unsigned int getId() const;
		glm::vec2 getTextureGridSize() const;

	private:
		unsigned int mId;
		glm::vec2 mTextureGridSize; // TODO: Find a good way to set this - probably a meta file inside the resource pack
	};
}