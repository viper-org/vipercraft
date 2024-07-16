#include <Game/Player/Player.h>

namespace ViperCraft
{
	Player::Player()
		: mPosition(nullptr)
		, mController(*this)
	{
	}

	void Player::init()
	{
		mController.init();
	}

	PlayerController& Player::getPlayerController()
	{
		return mController;
	}
}