#pragma once

#include<glad/glad.h>
#include<string>
namespace Core::Renderer::Drawable {
	class Texture2D {
	public:
		Texture2D(const GLuint width, GLuint height,
			const unsigned char* data, const unsigned int chanels = 4u,
			const GLenum filter = GL_LINEAR,
			const  GLenum wrapMode = GL_CLAMP_TO_EDGE);
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2D) noexcept;
		Texture2D(Texture2D&& texture2D) noexcept;
		void bind() const;
		~Texture2D();
	private:

	private:
		GLuint _ID;
		GLenum _mode;
		unsigned int _width = 0u;
		unsigned int _height = 0u;
	};
}

