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
		void quad(std::array<glm::vec3, 4> corners, glm::vec2 texCoords);
		void bindModels();

		RenderQueue* mParent;
		int mId;

		std::vector<float> mVertices; // x, y, z, w, tex_x, tex_y
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
		void quad(int bufferId, std::array<glm::vec3, 4> corners, glm::vec2 texCoords);
		void bindModels(int bufferId);

		void draw();

	private:
		std::unique_ptr<ShaderProgram> mMainShader;
		std::unique_ptr<TextureAtlas> mTextureAtlas;
		std::unique_ptr<Cam> mCam;
		Camera& mCamera;

		std::vector<RenderBuffer> mBuffers;

		RenderBuffer* findBuffer(int bufferId);
	};
}