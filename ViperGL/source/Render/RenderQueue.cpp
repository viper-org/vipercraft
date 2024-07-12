#include <ViperGL/Render/RenderQueue.h>

#include <Render/Renderable.h>
#include <Render/RenderableRect.h>
#include <Render/RenderableVoxel.h>
#include <Render/Cam.h>

#include <Shader/Shader.h>

namespace ViperGL
{
	RenderQueue::RenderQueue(Camera& camera)
		: mCamera(camera)
	{
		mCamera.updateVectors();
	}

	RenderQueue::~RenderQueue()
	{
	}

	void RenderQueue::init()
	{
		ShaderErrorCode ec;
		mMainShader = std::make_unique<ShaderProgram>("main", ec); // TODO: check error code and return another if failed
		mCam = std::make_unique<Cam>(mCamera, mMainShader->getId());
	}

	static int lastRenderableID = 0;
	int RenderQueue::push(const Rect& rect)
	{
		mRenderables.push_back(std::make_unique<RenderableRect>(mMainShader.get()));
		mRenderables.back()->init(lastRenderableID);
		return lastRenderableID++;
	}

	int RenderQueue::push(const Voxel& voxel)
	{
		mRenderables.push_back(std::make_unique<RenderableVoxel>(mMainShader.get(), Texture(voxel.mTextureName)));
		mRenderables.back()->init(lastRenderableID);
		return lastRenderableID++;
	}

	void RenderQueue::prepareDraw()
	{
		mCamera.updateVectors();

		mCamera.yaw = fmodf(mCamera.yaw, 360.f);
		mCam->updateMatrices();
	}

	void RenderQueue::drawRenderable(int id, glm::vec3 position)
	{
		mRenderables[id]->drawAt(position);
	}
}