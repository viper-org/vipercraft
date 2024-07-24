#pragma once

#include <glm/vec3.hpp>

#include <vector>

namespace ViperCraft
{
	class Tile;

	namespace Feature
	{
		class OreFeature
		{
		public:
			OreFeature(Tile* tile, int minHeight, int maxHeight, int attemptsPerChunk, float rarity, float initialExpansionChance, float expandChance);

			void generateInChunk(glm::vec3 chunkPos) const;

			static const std::vector<OreFeature>& GetOreFeatures();

		private:
			Tile* mTile;

			int mMinHeight;
			int mMaxHeight;

			int mAttemptsPerChunk;
			float mRarity;
			float mInitialExpansionChance;
			float mExpandChance;

			void placeAt(glm::vec3 pos, float currChance) const;
		};
	}
}