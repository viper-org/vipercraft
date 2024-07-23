#include <ViperGL/Render/UI.h>

#include <Shader/Shader.h>

#include <glad/glad.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <optional>

namespace ViperGL
{
	namespace UI
	{
		static std::optional<ShaderProgram> shader;
		static glm::mat4 ortho;

		void InitUIRenderer(float aspectRatio)
		{
			ShaderErrorCode ec;
			shader = ShaderProgram("ui", ec);
			ortho = glm::ortho(-1.f * aspectRatio, 1.f * aspectRatio, -1.f, 1.f);
			glLineWidth(3.75f);
		}

		void PreDraw()
		{
			shader->use();

			int orthoLoc = glGetUniformLocation(shader->getId(), "ortho");
			glUniformMatrix4fv(orthoLoc, 1, GL_FALSE, glm::value_ptr(ortho));
		}

		void DrawLine(glm::vec2 from, glm::vec2 to, Color color)
		{
			float vertices[] = {
				from.x, from.y, color.x, color.y, color.z, color.w,
				to.x, to.y, color.x, color.y, color.z, color.w,
			};

			constexpr unsigned int INDICES[] = {
				0, 1,
			};

			unsigned int vao, vbo, ebo;
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// vertices
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)0);
			// color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)(2 * sizeof(vertices[0])));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

			glBindVertexArray(vao);
			glDrawElements(GL_LINES, sizeof(INDICES) / sizeof(INDICES[0]), GL_UNSIGNED_INT, 0);
		}
	}
}