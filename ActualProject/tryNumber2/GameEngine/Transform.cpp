#include "Transform.h"

Transform::Transform(vec3 position, vec3 scale, quat rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = normalize(rotation);
}

void Transform::Rotate(vec3 axis, GLfloat degree)
{
	rotation = normalize(rotate(rotation, degree, axis));
}

void Transform::SetPosition(vec3 position)
{
	this->position = position;
}

void Transform::Translate(vec3 delta)
{
	position += delta;
}

void Transform::SetScale(vec3 scale)
{
	this->scale = scale;
}

void Transform::bind(GLuint shaderProgram)
{
	mat4 matrix = getMatrixModel();
	GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

vec3 Transform::GetPosition()
{
	return position;
}

vec3 Transform::GetScale()
{
	return scale;
}

quat Transform::GetRotation()
{
	return rotation;
}

vec3 Transform::GetForward()
{
	return normalize(vec3(getMatrixModel() * vec4(0, 0, 1 ,0)));
}

vec3 Transform::GetRight()
{
	return normalize(vec3(getMatrixModel() * vec4(1, 0, 0, 0)));
}

vec3 Transform::GetUp()
{
	return normalize(vec3(getMatrixModel() * vec4(0, 1, 0, 0)));
}

void Transform::SetParent(Transform * parent)
{
	this->parent = parent;
}

Transform * Transform::GetParent()
{
	return parent;
}

void Transform::LookAt(vec3 lookTo)
{
	rotation = quat(lookAt(GetPosition(), position + lookTo, GetUp()));
}


mat4 Transform::getParentMatrix()
{
	if (parent == nullptr)
		return mat4();
	return parent->getMatrixModel();
}

mat4 Transform::getMatrixModel()
{
	mat4 matrix = translate(mat4(), position);
	matrix *= glm::scale(matrix, scale);
	matrix *= mat4(rotation);
	return getParentMatrix() * matrix;
}
