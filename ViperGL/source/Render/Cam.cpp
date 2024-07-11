#include <Render/Cam.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ViperGL
{
	Cam::Cam(unsigned int shaderId)
		: mProj(glm::mat4(1.f))
		, mModel(glm::mat4(1.f))
		, mView(glm::mat4(1.f))
		, mPosition(glm::vec3(0.f, 0.f, 3.f))
		, mTarget(glm::vec3(0.f, 0.f, 0.f))
		, mFront(glm::vec3(0.f, 0.f, -1.f))
		, mBackward(glm::normalize(mPosition - mTarget))
		, mRight(glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), mBackward)))
		, mUp(glm::cross(mBackward, mRight))
		, mShaderId(shaderId)
	{
		mModel = glm::rotate(mModel, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		mView = glm::translate(mView, glm::vec3(0.0f, 0.0f, -3.0f));
		mProj = glm::perspective(glm::radians(45.0f), 1920.f / 1080.f, 0.1f, 100.0f); // TODO: Render distance and proper aspect ratio
	}

	void Cam::updateMatrices(float pitch, float yaw, float x, float y, float z)
	{
		mPosition = glm::vec3(x, y, z);

		// set direction based on pitch and yaw
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		mFront = glm::normalize(direction);

		// Set direction vectors and view
		mBackward = glm::normalize(mPosition - mTarget);
		mRight = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), mBackward));
		mUp = glm::cross(mBackward, mRight);

		mView = glm::lookAt(mPosition, mPosition + mFront, mUp);

		int model = glGetUniformLocation(mShaderId, "model");
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(mModel));

		int view = glGetUniformLocation(mShaderId, "view");
		glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(mView));

		int proj = glGetUniformLocation(mShaderId, "proj");
		glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(mProj));
	}
}