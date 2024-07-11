#include <Render/RenderableVoxel.h>

namespace ViperGL
{
	RenderableVoxel::RenderableVoxel(float x, float y, float z, ShaderProgram* shader, Texture texture)
		: x(x)
		, y(y)
		, z(z)
		, mTex(texture)
	{
		mShaderProgram = shader;
		mPosition = glm::vec3(x, y, z);
		mTexture = &mTex;
	}

	void RenderableVoxel::init()
	{
		mVO.~VertexObject();
		new (&mVO) VertexObject({
			 -0.5f, -0.5f, 0.5f, 0, 0,
			 0.5f, -0.5f, 0.5f, 1, 0,
			 0.5f, 0.5f, 0.5f, 1, 1,
			 -0.5f, 0.5f, 0.5f, 0, 1,

			 0.5f, -0.5f, -0.5f, 0, 0,
			 -0.5f, -0.5f, -0.5f, 1, 0,
			 -0.5f, 0.5f, -0.5f, 1, 1,
			 0.5f, 0.5f, -0.5f, 0, 1,

			 -0.5f, -0.5f, -0.5f, 0, 0,
			 -0.5f, -0.5f, 0.5f, 1, 0,
			 -0.5f, 0.5f, 0.5f, 1, 1,
			 -0.5f, 0.5f, -0.5f, 0, 1,

			 0.5f, -0.5f, 0.5f, 0, 0,
			 0.5f, -0.5f, -0.5f, 1, 0,
			 0.5f, 0.5f, -0.5f, 1, 1,
			 0.5f, 0.5f, 0.5f, 0, 1,
			 
			 -0.5f, 0.5f, 0.5f, 0, 0,
			 0.5f, 0.5f, 0.5f, 1, 0,
			 0.5f, 0.5f, -0.5f, 1, 1,
			 -0.5f, 0.5f, -0.5f, 0, 1,
			 
			 -0.5f, -0.5f, 0.5f, 0, 0,
			 0.5f, -0.5f, 0.5f, 1, 0,
			 0.5f, -0.5f, -0.5f, 1, 1,
			 -0.5f, -0.5f, -0.5f, 0, 1,
			});

		mEB.~ElementBuffer();
		new (&mEB) ElementBuffer({
			0, 1, 2,
			0, 2, 3,
			4,5,6,
			4,6,7,
			8,9,10,
			8,10,11,
			12,13,14,
			12,14,15,
			16,17,18,
			16,18,19,
			20,21,22,
			20,22,23,
		});
	}
}