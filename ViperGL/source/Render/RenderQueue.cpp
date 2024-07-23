#include <ViperGL/Render/RenderQueue.h>

#include <Render/Cam.h>

#include <Shader/Shader.h>

#include <Texture/Texture.h>

#include <glad/glad.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	void RenderBuffer::quad(std::array<glm::vec3, 4> corners, glm::vec2 texCoords, float light, float alpha)
	{
		texCoords.y = (mParent->mTextureAtlas->getTextureGridSize().y - 1) - texCoords.y;
		float vertices[] = {
			corners[0][0], corners[0][1], corners[0][2],
				(1.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (1.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light, alpha,
			corners[1][0], corners[1][1], corners[1][2],
				(1.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (0.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light, alpha,
			corners[2][0], corners[2][1], corners[2][2],
				(0.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (0.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light, alpha,
			corners[3][0], corners[3][1], corners[3][2],
				(0.f + texCoords.x) / mParent->mTextureAtlas->getTextureGridSize().x, (1.f + texCoords.y) / mParent->mTextureAtlas->getTextureGridSize().y, light, alpha,
		};

		static unsigned int INDICES[] = {
			0, 1, 3,
			1, 2, 3,
		};

		unsigned int correctedIndices[6];
		for (auto i = 0; i < 6; ++i)
		{
			correctedIndices[i] = INDICES[i] + mVertices.size() / 7;
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(mVertices[0]), (void*)0);
		// texture coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(mVertices[0]), (void*)(3 * sizeof(mVertices[0])));
		// light data
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(mVertices[0]), (void*)(5 * sizeof(mVertices[0])));
		// transparency
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(mVertices[0]), (void*)(6 * sizeof(mVertices[0])));

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

	void RenderQueue::quad(int bufferId, std::array<glm::vec3, 4> corners, glm::vec2 texCoords, float light, float alpha)
	{
		if (auto buffer = findBuffer(bufferId))
		{
			buffer->quad(corners, texCoords, light, alpha);
		}
	}

	void RenderQueue::bindModels(int bufferId)
	{
		if (auto buffer = findBuffer(bufferId))
		{
			buffer->bindModels();
		}
	}

	void RenderQueue::prepareDraw()
	{
		mMainShader->use();

		mCamera.updateVectors();

		mCam->updateMatrices();
	}

	void RenderQueue::draw(int bufferId)
	{
		if (auto buffer = findBuffer(bufferId))
		{
			glBindVertexArray(buffer->mVAO);
			glDrawElements(GL_TRIANGLES, buffer->mIndices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	RenderBuffer* RenderQueue::findBuffer(int id)
	{
		auto it = std::find_if(mBuffers.begin(), mBuffers.end(), [id](const auto& buffer) {
			return buffer.mId == id;
			});
		return &*it;
	}


	UIRenderQueue::UIRenderQueue()
		: mVAO(0)
		, mVBO(0)
		, mEBO(0)
	{
	}

	UIRenderQueue::~UIRenderQueue()
	{
	}

	void UIRenderQueue::init(float aspectRatio)
	{
		ShaderErrorCode ec;
		mShader = std::make_unique<ShaderProgram>("ui", ec); // TODO: check error code and return another if failed
		mOrtho = glm::ortho(-1.f * aspectRatio, 1.f * aspectRatio, -1.f, 1.f);
		glLineWidth(3.75f);
	}

	void UIRenderQueue::reset()
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		glDeleteBuffers(1, &mEBO);

		mVertices.clear();
		mIndices.clear();
	}

	void UIRenderQueue::line(glm::vec2 from, glm::vec2 to, Color color)
	{
		float vertices[] = {
			from.x, from.y, color.x, color.y, color.z, color.w,
			to.x, to.y, color.x, color.y, color.z, color.w,
		};

		constexpr unsigned int INDICES[] = {
			0, 1,
		};

		unsigned int correctedIndices[2];
		for (auto i = 0; i < 2; ++i)
		{
			correctedIndices[i] = INDICES[i] + mVertices.size() / 6;
		}

		std::copy(std::begin(vertices), std::end(vertices), std::back_inserter(mVertices));
		std::copy(std::begin(correctedIndices), std::end(correctedIndices), std::back_inserter(mIndices));
	}

	void UIRenderQueue::bind()
	{
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), mVertices.data(), GL_STATIC_DRAW);

		// vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(mVertices[0]), (void*)0);
		// color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(mVertices[0]), (void*)(2 * sizeof(float)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(mIndices[0]), mIndices.data(), GL_STATIC_DRAW);
	}

	void UIRenderQueue::draw()
	{
		mShader->use();

		int ortho = glGetUniformLocation(mShader->getId(), "ortho");
		glUniformMatrix4fv(ortho, 1, GL_FALSE, glm::value_ptr(mOrtho));

		glBindVertexArray(mVAO);
		glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0);
	}
}