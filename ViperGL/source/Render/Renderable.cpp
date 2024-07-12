#include <Render/Renderable.h>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace ViperGL
{
	void Renderable::drawAt(glm::vec3 position)
	{
		mTexture->bind();
		mShaderProgram->use();
		mVO.bind();

		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, position);
		int modelLocation = glGetUniformLocation(mShaderProgram->getId(), "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, mEB.getSize(), GL_UNSIGNED_INT, 0);
	}

	int Renderable::getId() const
	{
		return mId;
	}
}