#pragma once

#include <ViperGL/Camera/Camera.h>

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace ViperGL
{
	class ShaderProgram;
	class TextureAtlas;
	class Cam;

	using Color = glm::vec4;

	namespace Colors
	{
		constexpr glm::vec4 White = glm::vec4(1.f, 1.f, 1.f, 1.f);
		constexpr glm::vec4 Black = glm::vec4(0.f, 0.f, 0.f, 1.f);
	}

	struct TextureCoords
	{
		float x;
		float y;
	};

	class RenderBuffer
	{
	friend class RenderQueue;
	public:
		RenderBuffer(RenderQueue* parent, int id);

	private:
		void resetModels();
		void quad(std::array<glm::vec3, 4> corners, glm::vec2 texCoords, float light, float alpha);
		void bindModels();

		RenderQueue* mParent;
		int mId;

		std::vector<float> mVertices; // x, y, z, tex_x, tex_y
		std::vector<unsigned int> mIndices;

		unsigned int mVAO;
		unsigned int mVBO;
		unsigned int mEBO;
	};
	
	class RenderQueue
	{
	friend class RenderBuffer;
	public:
		RenderQueue(Camera& camera);
		~RenderQueue();

		void init(const std::string& textureAtlasPath);

		int newBuffer();
		void removeBuffer(int buffer);

		void resetModels(int bufferId);
		void quad(int bufferId, std::array<glm::vec3, 4> corners, glm::vec2 texCoords, float light, float alpha);
		void bindModels(int bufferId);

		void prepareDraw();
		void draw(int bufferId);

	private:
		std::unique_ptr<ShaderProgram> mMainShader;
		std::unique_ptr<TextureAtlas> mTextureAtlas;
		std::unique_ptr<Cam> mCam;
		Camera& mCamera;

		std::vector<RenderBuffer> mBuffers;

		RenderBuffer* findBuffer(int bufferId);
	};

	class UIRenderQueue
	{
	public:
		UIRenderQueue();
		~UIRenderQueue();

		void init(float aspectRatio);

		void reset();
		void line(glm::vec2 from, glm::vec2 to, Color);
		void bind();

		void draw();

	private:
		std::unique_ptr<ShaderProgram> mShader;

		glm::mat4 mOrtho;

		std::vector<float> mVertices; // x, y
		std::vector<unsigned int> mIndices;

		unsigned int mVAO;
		unsigned int mVBO;
		unsigned int mEBO;
	};
}