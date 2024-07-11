#pragma once

#include <Shader/Shader.h>

#include <Vertex/ElementBuffer.h>
#include <Vertex/VertexObject.h>

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
	};
}