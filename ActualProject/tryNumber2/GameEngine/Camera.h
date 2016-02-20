#ifndef __CAMERA__H
#define __CAMERA__H

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Object.h"
#include "Screen.h"

using namespace glm;

class Camera : public Component
{
public:
	Camera(Screen* screen);

	void SetOrthographicView(GLfloat zoom);

	void SetPerspective(GLfloat angle = 45.0f, GLfloat near = 0.1f, GLfloat far = 1000);

	void SetViewPort(vec2 pos, vec2 size);
	void Renderer(vector<Object*>* objects);

	virtual void Update(double deltaTime);

private:
	Screen* screen;

	vec2 viewPortPos;
	vec2 viewPortsize;

	mat4 getViewMatrix();

	bool isPerspective = true;

	//To perspective
	GLfloat angle = 45, near = 0.1f, far = 1000.0f;

	//To othographic
	GLfloat zoom;

	friend void SetObject(Component*, Object*);
};

#endif
