#pragma once

#include <glm/mat4x4.hpp>

namespace ViperGL
{
	class Cam
	{
	public:
		Cam(unsigned int shaderId);

		void updateMatrices(float pitch, float yaw);

	private:
		glm::mat4 mProj;
		glm::mat4 mModel;
		glm::mat4 mView;
		
		glm::vec3 mPosition;
		glm::vec3 mTarget;

		glm::vec3 mFront;
		glm::vec3 mBackward;
		glm::vec3 mRight;
		glm::vec3 mUp;

		unsigned int mShaderId;
	};
}