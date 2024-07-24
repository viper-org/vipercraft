#include <Game/Player/PlayerController.h>
#include <Game/Player/Player.h>

#include <Game/World/World.h>

#include <ViperCraft/ViperCraft.h>

#include <Physics/Collider.h>
#include <Physics/Raycast.h>

#include <Input/Input.h>

#include <iostream>

namespace ViperCraft
{
	PlayerController::PlayerController(Player& parent)
		: mParent(parent)
		, mAcceleration(0,0,0)
		, mVelocity(0,0,0)
	{
	}
	
	void PlayerController::init()
	{
		auto handler = std::bind(&PlayerController::onTick, this, std::placeholders::_1);
		ViperCraft::GetInstance()->onTick(handler);

		Input::OnMouseButtonDown(Input::MouseButton::Left,  std::bind(&PlayerController::onLeftMouseClick,  this));
		Input::OnMouseButtonDown(Input::MouseButton::Right, std::bind(&PlayerController::onRightMouseClick, this));
	}

	ViperGL::Camera& PlayerController::getCamera()
	{
		return mCamera;
	}

	
	void PlayerController::doCollisions(double deltaTime)
	{
		// returns the new value of the passed axis
		auto checkAxis = [this, deltaTime](float axis, glm::vec3 component) -> float {
			constexpr float PLAYER_SIZE = 0.6f;

			auto newPosition = mParent.mPosition + component * (float)deltaTime;

			// Create the player bounding box
			std::array<glm::vec3, 4> playerCorners = {
				newPosition + mCamera.forward * PLAYER_SIZE + mCamera.right * PLAYER_SIZE,
				newPosition + mCamera.forward * PLAYER_SIZE - mCamera.right * PLAYER_SIZE,
				newPosition - mCamera.forward * PLAYER_SIZE + mCamera.right * PLAYER_SIZE,
				newPosition - mCamera.forward * PLAYER_SIZE - mCamera.right * PLAYER_SIZE,
			};
			auto minX = std::min_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
				return a.x < b.x;
				})->x;
			auto maxX = std::max_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
				return a.x < b.x;
				})->x;
			auto minZ = std::min_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
				return a.z < b.z;
				})->z;
			auto maxZ = std::max_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
				return a.z < b.z;
				})->z;
			Physics::BoundingBox playerBB = Physics::BoundingBox(glm::vec3(minX, newPosition.y, minZ), glm::vec3(maxX, newPosition.y + 1.8f, maxZ));

			glm::vec3 blockPos = glm::vec3(floor(newPosition.x), floor(newPosition.y), floor(newPosition.z));
			auto nearest = {
				blockPos,
			};

			auto doCollision = [this, playerBB, &axis](const glm::vec3& position) {
				auto chunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(position);
				if (!chunk) return;
				auto tile = chunk->getTile(position);
				if (!tile || !tile->isSolidTile()) return;

				Physics::BoundingBox block = Physics::BoundingBox(position, position + 1.f);
				Physics::Collision coll;
				auto collided = playerBB.collide(block, coll);
				if (collided)
				{
					axis = 0;
				}
			};
			for (auto& position : nearest)
			{
				auto topPosition = position + glm::vec3(0.f, 1.f, 0.f);

				doCollision(position);
				doCollision(topPosition);
			}
			return axis;
		};

		mVelocity.x = checkAxis(mVelocity.x, glm::vec3(mVelocity.x, 0.f, 0.f));
		mVelocity.z = checkAxis(mVelocity.z, glm::vec3(0.f, 0.f, mVelocity.z));
	}

	void PlayerController::updatePosition(double deltaTime)
	{
		constexpr float CAMERA_HEIGHT = 1.62f;

		mParent.mPosition += mVelocity * (float)deltaTime;
		mCamera.position = mParent.mPosition + glm::vec3(0, CAMERA_HEIGHT, 0);
	}

	void PlayerController::processInput()
	{
		if (!ViperCraft::GetInstance()->isGameInFocus())
		{
			return;
		}

		if (isSprinting())
		{
			mParent.mMoveSpeed *= 1.3f;
			mCamera.fov = 99.f;
		}
		else
		{
			mCamera.fov = 90.f;
		}

		glm::vec3 move = glm::vec3(0.f);
		if (Input::GetButtonDown(Input::Key::A))
		{
			auto step = -mCamera.right * mParent.mMoveSpeed;
			move += step;
		}
		if (Input::GetButtonDown(Input::Key::D))
		{
			auto step = mCamera.right * mParent.mMoveSpeed;
			move += step;
		}
		if (Input::GetButtonDown(Input::Key::W))
		{
			auto step = mCamera.forward * mParent.mMoveSpeed;
			move += step;
		}
		if (Input::GetButtonDown(Input::Key::S))
		{
			auto step = -mCamera.forward * mParent.mMoveSpeed;
			move += step;
		}

		if ((isPlayerGroundedAt(mParent.mPosition) || isPlayerInWater()) && Input::GetButtonDown(Input::Key::Space))
		{
			constexpr float JUMP_FORCE = 150;
			mAcceleration.y += JUMP_FORCE * mParent.mJumpHeight;
		}

		if (Input::GetButtonDown(Input::Key::R))
		{
			mParent.mPosition = ViperCraft::GetInstance()->getWorld()->getSpawnPoint();
			mAcceleration = glm::vec3(0.f);
			mVelocity = glm::vec3(0.f);
		}
		if (Input::GetButtonDown(Input::Key::RCtrl))
		{
			ViperCraft::GetInstance()->getWorld()->saveToFile("test.vcwrld");
		}
		if (Input::GetButtonDown(Input::Key::RShift))
		{
			ViperCraft::GetInstance()->getWorld()->clear();
			World::LoadFromFile(*ViperCraft::GetInstance()->getWorld(), "test.vcwrld");
		}

		mVelocity += move;

		mCamera.yaw += Input::GetInputAxis(Input::InputAxis::AxisX);
		mCamera.pitch += Input::GetInputAxis(Input::InputAxis::AxisY);

		mCamera.pitch = glm::clamp(mCamera.pitch, -89.9f, 89.9f);
	}

	bool PlayerController::isSprinting()
	{
		return Input::GetButtonDown(Input::Key::LShift);
	}

	void PlayerController::onTick(double deltaTime)
	{
		mVelocity = mAcceleration * (float)deltaTime;
		checkGroundedness(deltaTime);
		processInput();
		doCollisions(deltaTime);
		updatePosition(deltaTime);
	}

	void PlayerController::onLeftMouseClick()
	{
		if (!ViperCraft::GetInstance()->isGameInFocus()) {
			return;
		}

		Physics::RaycastHit hit;
		if (Physics::RaycastSolid(mParent.mPosition + glm::vec3(0.f, 1.6f, 0.f), mCamera.front, 3.f, hit))
		{
			auto chunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(hit.point);
			chunk->getTile(hit.point) = nullptr; // air
			auto surroundings = Tile::GetSurroundings(hit.point);
			for (auto& position : surroundings)
			{
				auto tile = ViperCraft::GetInstance()->getWorld()->getTile(position);
				if (tile) tile->update(position);
			}
			chunk->chunkUpdated();
		}
	}

	void PlayerController::onRightMouseClick()
	{
		if (!ViperCraft::GetInstance()->isGameInFocus()) {
			return;
		}

		Physics::RaycastHit hit;
		if (Physics::RaycastSolid(mParent.mPosition + glm::vec3(0.f, 1.6f, 0.f), mCamera.front, 3.f, hit))
		{
			auto newBlockPos = floor(hit.point + hit.normal);

			// make sure we aren't placing a block inside the player
			if (newBlockPos != floor(mParent.mPosition) && newBlockPos != floor(mParent.mPosition) + glm::vec3(0.f, 1.f, 0.f))
			{
				auto chunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(newBlockPos);
				chunk->getTile(newBlockPos) = Tile::GetTile("cobblestone");
				chunk->chunkUpdated();
			}
		}
	}

	void PlayerController::checkGroundedness(double deltaTime)
	{
		if (!isPlayerGroundedAt(mParent.mPosition + glm::vec3(0.f, mVelocity.y, 0.f) * (float)deltaTime))
		{
			if (isPlayerInWater())
			{
				mParent.mJumpHeight = 1.5f;
				mAcceleration.y = -100.f;
			}
			else
			{
				mParent.mJumpHeight = 1.25f;
				mAcceleration.y -= 15.f;
			}
			mParent.mMoveSpeed = 2.f;
		}
		else
		{
			mAcceleration.y = 0.f;
			mParent.mMoveSpeed = 4.317f;
		}
	}

	bool PlayerController::isPlayerGroundedAt(glm::vec3 position)
	{
		Physics::RaycastHit hit;
		return (
			Physics::RaycastSolid(position, glm::vec3(0.f, -1.f, 0.f),   0.3f, hit)
		);
	}

	bool PlayerController::isPlayerInWater()
	{
		auto tile = ViperCraft::GetInstance()->getWorld()->getTile(mParent.mPosition);
		if (!tile || !tile->isLiquid()) return false;
		return true;
	}
}
