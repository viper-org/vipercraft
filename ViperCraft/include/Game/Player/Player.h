#pragma once

#include <Game/Player/PlayerController.h>

#include <glm/vec3.hpp>

namespace ViperCraft
{
	class Player
	{
	friend class PlayerController;
	friend class ViperCraft;
	public:
		Player();

		void init();
		
		const glm::vec3& getPosition() const;
		PlayerController& getPlayerController();

	private:
		glm::vec3 mPosition;

		float mMoveSpeed;
		float mJumpHeight; // in blocks

		PlayerController mController;
	};
}