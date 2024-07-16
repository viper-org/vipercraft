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
		, mCamera(camera)
		, mShaderId(shaderId)
	{
		mProj = glm::perspective(glm::radians(90.f), 1920.f / 1080.f, 0.1f, 100.f); // TODO: Render distance and proper aspect ratio
	}

	void Cam::updateMatrices()
	{
		mView = glm::lookAt(mCamera.position, mCamera.position + mCamera.front, mCamera.up);

		int view = glGetUniformLocation(mShaderId, "view");
		glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(mView));

		int proj = glGetUniformLocation(mShaderId, "proj");
		glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(mProj));
	}
}