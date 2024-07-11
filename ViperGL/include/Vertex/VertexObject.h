#pragma once

#include <initializer_list>

namespace ViperGL
{
	class VertexObject
	{
	public:
		VertexObject(std::initializer_list<float> vertices);
		~VertexObject();

		void bind();

	private:
		unsigned int mVBO;
		unsigned int mVAO;
	};
}