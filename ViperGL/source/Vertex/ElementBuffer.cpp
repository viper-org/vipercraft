#include <Vertex/ElementBuffer.h>

#include <glad/glad.h>

namespace ViperGL
{
	ElementBuffer::ElementBuffer(std::initializer_list<unsigned int> indices)
		: mEBO(0)
		, mSize(indices.size())
	{
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(*indices.begin()), indices.begin(), GL_STATIC_DRAW);
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &mEBO);
	}

	int ElementBuffer::getSize() const
	{
		return mSize;
	}
}