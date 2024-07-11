#pragma once

#include <Shader/Shader.h>

#include <Texture/Texture.h>

#include <Vertex/ElementBuffer.h>
#include <Vertex/VertexObject.h>

#include <glm/vec3.hpp>

namespace ViperGL
{
	class Renderable
	{
	public:
		virtual void init() = 0;

		void draw();
		
	protected:
		VertexObject mVO;
		ElementBuffer mEB;
		ShaderProgram* mShaderProgram{ nullptr };
		Texture* mTexture{ nullptr };

		glm::vec3 mPosition{ 0.f, 1.f, 0.f };
	};
}