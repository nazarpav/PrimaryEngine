#pragma once
#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "../Shaders/ShaderProgram.h"
#include "../../Core/Transform.h"
#include "Texture2D.h"
#include <string>
#include <memory>
namespace Core::Renderer::Drawable {
	class Sprite {
	public:
		Sprite(const std::shared_ptr<Texture2D> texture, const std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> shaderProgram, const Transform& transform);
		~Sprite();
		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		void Draw()const;
		glm::vec2 GetOriginSize();
		const Transform& GetTransform() const;
		void SetTransform(const Transform& val);
	private:
		std::shared_ptr<Texture2D> _texture;
		std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> _shaderProgram;
		Transform _transform;
		glm::vec2 _originSize;
		GLuint _VAO;
		GLuint _vCoordVBO;
		GLuint _texCoordVBO;
	};
}
