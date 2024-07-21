#pragma once

#include <ViperGL/Camera/Camera.h>

namespace ViperCraft
{
	class Player;

	class PlayerController
	{
	public:
		PlayerController(Player& parent);

		void init();

		ViperGL::Camera& getCamera();

	private:
		ViperGL::Camera mCamera;

		glm::vec3 mAcceleration;
		glm::vec3 mVelocity;

		Player& mParent;

		void doCollisions(double deltaTime);
		void updatePosition(double deltaTime);
		
		void processInput();

		void onTick(double deltaTime);
		void onLeftMouseClick();
		void onRightMouseClick();

		void checkGroundedness(double deltaTime);
		bool isPlayerGroundedAt(glm::vec3 position);
	};
}