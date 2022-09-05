#include "Sprite.h"
namespace Core::Renderer::Drawable {
	Sprite::Sprite(const std::shared_ptr<Texture2D> texture, const std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> shaderProgram, const Transform& transform) :
		_originSize(texture->GetTextureSize()),
		_texture(texture),
		_shaderProgram(shaderProgram),
		_transform(transform)
	{
		const GLfloat vCoord[] = {
			0.f, 0.f, 0.f,
			0.f, _originSize.y, 0.f,
			_originSize.x, _originSize.y, 0.f,
			_originSize.x, _originSize.y, 0.f,
			_originSize.x, 0.f, 0.f,
			0.f,0.f, 0.f
		/*	0.f, 0.f, 0.f,
			0.f, _originSize.y, 0.f,
			_originSize.x, _originSize.y, 0.f,
			_originSize.x, _originSize.y, 0.f,
			_originSize.x, 0.f, 0.f,
			0.f,0.f, 0.f*/
		};
		const GLfloat uvCoord[] = {
			/*0.f, 0.f, 
			0.f, _originSize.y, 
			_originSize.x, _originSize.y, 
			_originSize.x, _originSize.y, 
			_originSize.x, 0.f,
			0.f,0.f*/
			0.f,0.f,
			0.f,1.f,
			1.f,1.f,
			1.f,1.f,
			1.f,0.f,
			0.f,0.f
		};
		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);

		glGenBuffers(1, &_vCoordVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _vCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vCoord), &vCoord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &_texCoordVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoord), &uvCoord, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Sprite::~Sprite() {
		glDeleteBuffers(1, &_vCoordVBO);
		glDeleteBuffers(1, &_texCoordVBO);
		glDeleteVertexArrays(1, &_VAO);
	}

	void Sprite::Draw() const {
		_shaderProgram->Use();
		glBindVertexArray(_VAO);
		_shaderProgram->SetMatrix4("model_mat", _transform.GetMatrix());
		glActiveTexture(GL_TEXTURE0);
		_texture->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	glm::vec2 Sprite::GetOriginSize()
	{
		return glm::vec2();
	}

	const Transform& Sprite::GetTransform() const {
		return _transform;
	}

	void Sprite::SetTransform(const Transform& val) {
		_transform = val;
	}
}
