#pragma once

#include <string>

namespace ViperGL
{
	class Texture
	{
	public:
		Texture(const std::string& name);

		void bind();

		unsigned int getId() const;

	private:
		unsigned int mId;
	};
}