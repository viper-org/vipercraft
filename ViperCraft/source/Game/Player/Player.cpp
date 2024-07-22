#include <Game/Player/Player.h>

namespace ViperCraft
{
	Player::Player()
		: mPosition(0, 3.f, 0)
		, mMoveSpeed(4.317f)
		, mJumpHeight(1.25f)
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