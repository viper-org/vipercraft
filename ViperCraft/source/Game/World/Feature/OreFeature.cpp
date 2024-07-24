#include <Game/World/Feature/OreFeature.h>

#include <Game/Block/Tile.h>

#include <ViperCraft/ViperCraft.h>

namespace ViperCraft
{
	namespace Feature
	{
		std::vector<OreFeature> OreFeatures =
		{
			OreFeature(Tile::GetTile(Block::COAL_ORE), 0,  36, 15, 0.975f, 0.09f, 1.95f),
			OreFeature(Tile::GetTile(Block::COAL_ORE), 36, 64, 25, 0.9f,   0.09f, 1.55f),

			OreFeature(Tile::GetTile(Block::IRON_ORE), 0,  56, 15, 0.93f,  0.1f, 2.95f),

			OreFeature(Tile::GetTile(Block::GOLD_ORE), 0,  47, 5,  0.96f,  0.15f, 3.25f),


			OreFeature(Tile::GetTile(Block::DIRT), 0, 64, 7, 0.8f, 0.04f, 1.f),
		};

		OreFeature::OreFeature(Tile* tile, int minHeight, int maxHeight, int attemptsPerChunk, float rarity, float initialExpansionChance, float expandChance)
			: mTile(tile)
			, mMinHeight(minHeight)
			, mMaxHeight(maxHeight)
			, mAttemptsPerChunk(attemptsPerChunk)
			, mRarity(rarity)
			, mInitialExpansionChance(initialExpansionChance)
			, mExpandChance(expandChance)
		{
		}

		void OreFeature::generateInChunk(glm::vec3 chunkPos) const
		{
			for (auto i = 0; i < mAttemptsPerChunk; ++i)
			{
				if (rand() >= RAND_MAX * mRarity)
				{
					float x = rand() % 16;
					float y = (rand() % (mMaxHeight - mMinHeight) + mMinHeight);
					float z = rand() % 16;
					glm::vec3 pos = glm::vec3(x, y, z) + chunkPos;

					placeAt(pos, mInitialExpansionChance);
				}
			}
		}

		void OreFeature::placeAt(glm::vec3 pos, float currChance) const
		{
			auto world = ViperCraft::GetInstance()->getWorld();
			auto chunk = world->getPositionChunk(pos);
			if (!chunk) return;
			auto& tile = chunk->getTile(pos);
			if (!tile) return;
			if (tile->getId() == Block::STONE)
			{
				tile = mTile;
				for (const auto& pos : tile->GetSurroundings(pos))
				{
					if (rand() >= RAND_MAX * currChance)
					{
						placeAt(pos, currChance * mExpandChance + (float)(rand() % 35) / 10.f);
					}
				}
			}
		}


		const std::vector<OreFeature>& OreFeature::GetOreFeatures()
		{
			return OreFeatures;
		}
	}
}