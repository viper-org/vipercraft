#include <Game/Player/Player.h>

namespace ViperCraft
{
	Player::Player()
		: mPosition(3, 1.05, 3)
		, mController(*this)
	{
	}

	void Player::init()
	{
		mController.init();
	}

	const glm::vec3& Player::getPosition() const
	{
		return mPosition;
	}

	PlayerController& Player::getPlayerController()
	{
		return mController;
	}
}