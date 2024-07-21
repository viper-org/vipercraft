#include <ViperGL/Render/RenderQueue.h>

#include <Render/Cam.h>

#include <Shader/Shader.h>

#include <Texture/Texture.h>

#include <glad/glad.h>

#include <glm/ext/matrix_transform.hpp>

#include <algorithm>
#include <iterator>

namespace ViperGL
{
	RenderBuffer::RenderBuffer(RenderQueue* parent, int id)
		: mParent(parent)
		, mId(id)
		, mVAO(0)
		, mVBO(0)
		, mEBO(0)
	{
	}

	void RenderBuffer::resetModels()
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		glDeleteBuffers(1, &mEBO);

		mVertices.clear();
		mIndices.clear();
	}

	void RenderBuffer::quad(std::array<glm::vec3, 4> corners, glm::vec2 texCoords, float light)
	{
		float vertices[] = {
			corners[0][0], corners[0][1], corners[0][2],
				(1.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (1.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light,
			corners[1][0], corners[1][1], corners[1][2],
				(1.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (0.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light,
			corners[2][0], corners[2][1], corners[2][2],
				(0.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (0.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light,
			corners[3][0], corners[3][1], corners[3][2],
				(0.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (1.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light,
		};

		static unsigned int INDICES[] = {
			0, 1, 3,
			1, 2, 3,
		};

		unsigned int correctedIndices[6];
		for (auto i = 0; i < 6; ++i)
		{
			correctedIndices[i] = INDICES[i] + mVertices.size() / 6;
		}

		std::copy(std::begin(vertices), std::end(vertices), std::back_inserter(mVertices));
		std::copy(std::begin(correctedIndices), std::end(correctedIndices), std::back_inserter(mIndices));
	}

	void RenderBuffer::bindModels()
	{
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), mVertices.data(), GL_STATIC_DRAW);

		// vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(mVertices[0]), (void*)0);
		// texture coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(mVertices[0]), (void*)(3 * sizeof(mVertices[0])));
		// light data
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(mVertices[0]), (void*)(5 * sizeof(mVertices[0])));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(mIndices[0]), mIndices.data(), GL_STATIC_DRAW);
	}
	


	RenderQueue::RenderQueue(Camera& camera)
		: mCamera(camera)
	{
		mCamera.updateVectors();
	}

	RenderQueue::~RenderQueue()
	{
	}

	void RenderQueue::init(const std::string& textureAtlasPath)
	{
		ShaderErrorCode ec;
		mMainShader = std::make_unique<ShaderProgram>("main", ec); // TODO: check error code and return another if failed
		mTextureAtlas = std::make_unique<TextureAtlas>(textureAtlasPath);
		mCam = std::make_unique<Cam>(mCamera, mMainShader->getId());
	}

	int RenderQueue::newBuffer()
	{
		static int bufferID = 1;
		mBuffers.emplace_back(this, bufferID);
		return bufferID++;
	}

	void RenderQueue::removeBuffer(int id)
	{
		std::erase_if(mBuffers, [id](const auto& buffer) {
			return buffer.mId == id;
		});
	}

	void RenderQueue::resetModels(int bufferId)
	{
		if (auto buffer = findBuffer(bufferId))
		{
			buffer->resetModels();
		}
	}

	void RenderQueue::quad(int bufferId, std::array<glm::vec3, 4> corners, glm::vec2 texCoords, float light)
	{
		if (auto buffer = findBuffer(bufferId))
		{
			buffer->quad(corners, texCoords, light);
		}
	}

	void RenderQueue::bindModels(int bufferId)
	{
		if (auto buffer = findBuffer(bufferId))
		{
			buffer->bindModels();
		}
	}

	void RenderQueue::draw()
	{
		mCamera.updateVectors();

		mCam->updateMatrices();

		mMainShader->use();

		for (auto& buffer : mBuffers)
		{
			glBindVertexArray(buffer.mVAO);
			glDrawElements(GL_TRIANGLES, buffer.mIndices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	RenderBuffer* RenderQueue::findBuffer(int id)
	{
		auto it = std::find_if(mBuffers.begin(), mBuffers.end(), [id](const auto& buffer) {
			return buffer.mId == id;
			});
		return &*it;
	}
}