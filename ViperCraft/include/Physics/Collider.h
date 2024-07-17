#pragma once

#include <glm/vec3.hpp>

namespace ViperCraft
{
	namespace Physics
	{
		class BoundingBox
		{
		public:
			BoundingBox(glm::vec3 min, glm::vec3 max);

			bool intersects(const BoundingBox& other) const;

		private:
			glm::vec3 mMin;
			glm::vec3 mMax;
		};
	}
}