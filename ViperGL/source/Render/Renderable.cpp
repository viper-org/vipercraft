#include <ViperGL/Render/Renderable.h>

#include <glad/glad.h>

namespace ViperGL
{
	void Renderable::draw()
	{
		mShaderProgram->use();
		mVO.bind();
		glDrawElements(GL_TRIANGLES, mEB.getSize(), GL_UNSIGNED_INT, 0);
	}
}