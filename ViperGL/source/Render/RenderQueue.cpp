#include <ViperGL/Render/RenderQueue.h>

#include <Render/Renderable.h>
#include <Render/RenderableRect.h>
#include <Render/Cam.h>

#include <Shader/Shader.h>

namespace ViperGL
{
	RenderQueue::RenderQueue(Camera& camera)
		: mCamera(camera)
	{
	}

	RenderQueue::~RenderQueue()
	{
	}

	void RenderQueue::init()
	{
		ShaderErrorCode ec;
		mMainShader = std::make_unique<ShaderProgram>("main", ec); // TODO: check error code and return another if failed
		mCam = std::make_unique<Cam>(mMainShader->getId());
	}

	void RenderQueue::push(const Rect& rect)
	{
		mRenderables.push_back(std::make_unique<RenderableRect>(rect.x1, rect.y1, rect.x2, rect.y2, mMainShader.get()));
		mRenderables.back()->init();
	}

	void RenderQueue::draw()
	{
		mCamera.pitch = fmodf(mCamera.pitch, 360.f);
		mCamera.yaw = fmodf(mCamera.yaw, 360.f);
		mCam->updateMatrices(mCamera.pitch, mCamera.yaw);
		for (auto& r : mRenderables)
		{
			r->draw();
		}
	}
}