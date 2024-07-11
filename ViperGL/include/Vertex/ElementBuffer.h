#pragma once

#include <initializer_list>

namespace ViperGL
{
	class ElementBuffer
	{
	public:
		ElementBuffer(std::initializer_list<unsigned int> indices);
		~ElementBuffer();

	private:
		unsigned int mEBO;
	};
}