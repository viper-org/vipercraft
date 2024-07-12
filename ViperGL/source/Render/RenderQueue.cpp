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

	void RenderQueue::push(const Rect& rect)
	{
		mRenderables.push_back(std::make_unique<RenderableRect>(rect.x, rect.y, mMainShader.get()));
		mRenderables.back()->init();
	}

	void RenderQueue::push(const Voxel& voxel)
	{
		mRenderables.push_back(std::make_unique<RenderableVoxel>(voxel.mX, voxel.mY, voxel.mZ, mMainShader.get(), Texture(voxel.mTextureName)));
		mRenderables.back()->init();
	}

	void RenderQueue::draw()
	{
		mCamera.updateVectors();

		mCamera.yaw = fmodf(mCamera.yaw, 360.f);
		mCam->updateMatrices();
		for (auto& r : mRenderables)
		{
			r->draw();
		}
	}
}