#ifndef __TRANSFORM__H
#define __TRANSFORM__H

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glew\GL\glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;

class Transform
{
public:
	Transform(vec3 position = vec3(0, 0, 0), vec3 scale = vec3(1, 1, 1), quat rotation = quat(0, 0, 0, 1));

	void Rotate(vec3 axis, GLfloat degree);
	void SetPosition(vec3 position);
	void Translate(vec3 delta);
	void SetScale(vec3 scale);
	void bind(GLuint shaderProgram);

	vec3 GetPosition();
	vec3 GetScale();
	quat GetRotation();

	vec3 GetForward();
	vec3 GetRight();
	vec3 GetUp();

	void SetParent(Transform* parent);
	Transform* GetParent();
	void LookAt(vec3 lookTo);

private:
	vec3 position;
	vec3 scale;
	quat rotation;

	Transform* parent = nullptr;

	mat4 getParentMatrix();
	
	mat4 getMatrixModel();
};

#endif
