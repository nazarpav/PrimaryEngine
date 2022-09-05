#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
namespace Core {
	Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale) {
		SetPosition2D(position);
		SetRotation2D(rotation);
		SetScale2D(scale);
		_model = glm::mat4(1.f);
		UpdateMatrix();
	}
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		SetPosition(position);
		SetRotation(rotation);
		SetScale(scale);
		_model = glm::mat4(1.f);
		UpdateMatrix();
	}
	glm::vec3 Transform::GetPosition() const {
		return _position;
	}

	void Transform::SetPosition(const glm::vec3& position) {
		_position = position;
		UpdateMatrix();
	}

	glm::vec2 Transform::GetPosition2D() const {
		return glm::vec2(_position.x, _position.y);
	}

	void Transform::SetPosition2D(const glm::vec2& position) {
		SetPosition(glm::vec3(position, _position.z));
	}

	glm::vec3 Transform::GetRotation() const {
		return _rotation;
	}

	void Transform::SetRotation(const glm::vec3& rotation) {
		_rotation = rotation;
		UpdateMatrix();
	}

	float Transform::GetRotation2D() const {
		return _rotation.x;
	}

	void Transform::SetRotation2D(float rotation) {
		SetRotation(glm::vec3(rotation, _rotation.y, _rotation.z));
	}

	glm::vec3 Transform::GetScale() const {
		return _scale;
	}

	void Transform::SetScale(const glm::vec3& scale) {
		_scale = scale;
		UpdateMatrix();
	}

	glm::vec2 Transform::GetScale2D() const {
		return glm::vec2(_scale.x, _scale.y);
	}

	void Transform::SetScale2D(const glm::vec2& scale) {
		SetScale(glm::vec3(scale, _scale.z));
	}

	void Transform::Scale(const glm::vec3& scale) {
		_model = glm::scale(_model, scale);
	}

	void Transform::Scale(const glm::vec2& scale) {
		Scale(glm::vec3(scale, 0.f));
	}
	void Transform::UpdateMatrix() {
		_model = glm::translate(_model, _position);
		_model = glm::rotate(_model, glm::radians(_rotation.x), glm::vec3(0.f, 0.f, 1.f));
		_model = glm::scale(_model, _scale);
	}
	glm::mat4 Transform::GetMatrix() const {
		return _model;
	}
}
