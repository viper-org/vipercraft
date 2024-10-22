#pragma once

#include <ViperGL/Camera/Camera.h>

#include <glm/mat4x4.hpp>

namespace ViperGL
{
	class Cam
	{
	public:
		Cam(Camera& camera, unsigned int shaderId);

		void updateMatrices();

		glm::mat4 mProj;
		glm::mat4 mView;

		float mFov;
		
		Camera& mCamera;

		unsigned int mShaderId;
	};
}