#pragma once

#include <ViperGL/Render/Rect.h>
#include <ViperGL/Render/Voxel.h>

#include <ViperGL/Camera/Camera.h>

#include <memory>
#include <vector>

namespace ViperGL
{
	class Renderable;
	class ShaderProgram;
	class Cam;

	class RenderQueue
	{
	public:
		RenderQueue(Camera& camera);
		~RenderQueue();

		void init();

		int push(const Rect& rect);
		int push(const Voxel& voxel);

		void prepareDraw();
		void drawRenderable(int id, glm::vec3 position);

	private:
		std::vector<std::unique_ptr<Renderable> > mRenderables;
		std::unique_ptr<ShaderProgram> mMainShader;
		std::unique_ptr<Cam> mCam;
		Camera& mCamera;
	};
}