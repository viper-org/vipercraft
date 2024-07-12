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
		virtual void init(int id) = 0;

		void drawAt(glm::vec3 position);

		int getId() const;
		
	protected:
		VertexObject mVO;
		ElementBuffer mEB;
		ShaderProgram* mShaderProgram{ nullptr };
		Texture* mTexture{ nullptr };

		int mId;
	};
}