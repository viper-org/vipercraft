#include <Render/Cam.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ViperGL
{
	Cam::Cam(Camera& camera, unsigned int shaderId)
		: mProj(glm::mat4(1.f))
		, mView(glm::mat4(1.f))
		, mFov(90.f)
		, mCamera(camera)
		, mShaderId(shaderId)
	{
		mProj = glm::perspective(glm::radians(mFov), 1920.f / 1080.f, 0.01f, 100.f); // TODO: Proper aspect ratio
	}

	void Cam::updateMatrices()
	{
		if (mCamera.fov != mFov)
		{
			mFov = mCamera.fov;
			mProj = glm::perspective(glm::radians(mFov), 1920.f / 1080.f, 0.01f, 100.f);
		}
		mView = glm::lookAt(mCamera.position, mCamera.position + mCamera.front, mCamera.up);

		int view = glGetUniformLocation(mShaderId, "view");
		glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(mView));

		int proj = glGetUniformLocation(mShaderId, "proj");
		glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(mProj));
	}
}