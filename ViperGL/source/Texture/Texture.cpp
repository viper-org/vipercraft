#include <Texture/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

#include <filesystem>

namespace ViperGL
{
	TextureAtlas::TextureAtlas(const std::string& name)
		: mId(0)
		, mTextureGridSize(2, 1)
	{
		std::filesystem::path texturePath = std::filesystem::path(SHADER_SOURCE_DIR) / "texture" / (name + ".png");

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath.string().c_str(), &width, &height, &nrChannels, 0);

		glGenTextures(1, &mId);
		glBindTexture(GL_TEXTURE_2D, mId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// TODO: Error if other value

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	void TextureAtlas::bind()
	{
		glBindTexture(GL_TEXTURE_2D, mId);
	}

	unsigned int TextureAtlas::getId() const
	{
		return mId;
	}

	glm::vec2 TextureAtlas::getTextureGridSize() const
	{
		return mTextureGridSize;
	}
}