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

	private:
		glm::mat4 mProj;
		glm::mat4 mModel;
		glm::mat4 mView;
		
		Camera& mCamera;

		unsigned int mShaderId;
	};
}