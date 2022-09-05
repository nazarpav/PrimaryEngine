#pragma once
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
namespace Core {
	class Transform {
	public:
		Transform(glm::vec2 position = glm::vec2(0.f), float rotation = 0.f, glm::vec2 scale = glm::vec2(1.f));
		Transform(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
		glm::vec3 GetPosition() const;
		void SetPosition(const glm::vec3& val);
		glm::vec2 GetPosition2D() const;
		void SetPosition2D(const glm::vec2& val);
		glm::vec3 GetRotation() const;
		void SetRotation(const glm::vec3& val);
		float GetRotation2D() const;
		void SetRotation2D(float val);
		glm::vec3 GetScale() const;
		void SetScale(const glm::vec3& val);
		glm::vec2 GetScale2D() const;
		void SetScale2D(const glm::vec2& val);
		void Scale(const glm::vec3& val);
		void Scale(const glm::vec2& val);
		void UpdateMatrix();
		glm::mat4 GetMatrix() const;
	protected:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
		glm::mat4 _model;
	};
}

