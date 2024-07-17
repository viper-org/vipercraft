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

		Player& mParent;

		void onTick(double deltaTime);
		bool canPlayerMoveInto(glm::vec3 position);
	};
}