#pragma once

#include <glm/vec3.hpp>

namespace ViperCraft
{
	namespace Physics
	{
		// Casts a ray to the next solid block(or returns false if maxDist is reached first)
		bool RaycastSolid(glm::vec3 origin, glm::vec3 direction, float maxDist, glm::vec3& hit);
	}
}