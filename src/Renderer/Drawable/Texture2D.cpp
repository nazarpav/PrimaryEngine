#include "Texture2D.h"

Core::Renderer::Drawable::Texture2D::Texture2D(const GLuint width, GLuint height, const unsigned char* data, const unsigned int chanels, const GLenum filter, const GLenum wrapMode)
	: _width(width), _height(height) {
	switch (chanels) {
	case 4:
		_mode = GL_RGBA;
		break;
	case 3:
		_mode = GL_RGB;
		break;
	default:
		_mode = GL_RGB;
		break;
	}
	glGenTextures(1, &_ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D, 0, _mode, _width, _height, 0, _mode, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Core::Renderer::Drawable::Texture2D& Core::Renderer::Drawable::Texture2D::operator=(Texture2D&& texture2D) noexcept {
	glDeleteTextures(1, &_ID);
	_ID = texture2D._ID;
	texture2D._ID = 0;
	_mode = texture2D._mode;
	_width = texture2D._width;
	_height = texture2D._height;
	return *this;
}

Core::Renderer::Drawable::Texture2D::Texture2D(Texture2D&& texture2D) noexcept{
	_ID = texture2D._ID;
	texture2D._ID = 0;
	_mode = texture2D._mode;
	_width = texture2D._width;
	_height = texture2D._height;
}

void Core::Renderer::Drawable::Texture2D::bind() const {
	glBindTexture(GL_TEXTURE_2D, _ID);
}

Core::Renderer::Drawable::Texture2D::~Texture2D() {
	glDeleteTextures(1, &_ID);
}
