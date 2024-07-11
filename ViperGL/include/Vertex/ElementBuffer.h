#pragma once

#include <initializer_list>

namespace ViperGL
{
	class ElementBuffer
	{
	public:
		ElementBuffer() = default;
		ElementBuffer(std::initializer_list<unsigned int> indices);
		~ElementBuffer();

		int getSize() const;

	private:
		unsigned int mEBO;
		int mSize;
	};
}