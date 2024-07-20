#pragma once

#include <glm/vec3.hpp>

namespace ViperCraft
{
	namespace Physics
	{
		struct Collision
		{
			glm::vec3 normal;
			float depth;
		};

		class BoundingBox
		{
		public:
			BoundingBox(glm::vec3 min, glm::vec3 max);

			bool collide(const BoundingBox& other, Collision& collision) const;

		private:
			glm::vec3 mMin;
			glm::vec3 mMax;
		};
	}
}