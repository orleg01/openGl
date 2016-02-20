#include "Camera.h"

Camera::Camera(Screen * screen)
{
	this->screen = screen;
}

void Camera::SetOrthographicView(GLfloat zoom)
{
	this->zoom = zoom;
	isPerspective = false;
}

void Camera::SetPerspective(GLfloat angle, GLfloat near, GLfloat far)
{
	this->angle = angle;
	this->near = near;
	this->far = far;
}

void Camera::SetViewPort(vec2 pos, vec2 size)
{
	viewPortPos = pos;
	viewPortsize = size;
}

void Camera::Renderer(vector<Object*>* objects)
{
	glViewport((GLint)(viewPortPos.x * screen->getWidth()), (GLint)(viewPortPos.y * screen->getHeight()), 
			(GLint)(viewPortsize.x * screen->getWidth()), (GLint)(viewPortsize.y * screen->getHeight()));
	
	mat4 viewMatrix = getViewMatrix();

	for (Object* object : *objects)
	{
		object->Draw(viewMatrix);
	}
}

mat4 Camera::getViewMatrix()
{
	Transform& transform = object->GetTransform();
	vec3 center = transform.GetPosition() + transform.GetForward();

	mat4 projection;
	if (isPerspective)
	{
		projection = glm::perspective
			(angle, (screen->getWidth() * viewPortsize.x)/ (screen->getHeight() * viewPortsize.y), near, far);
	}
	else
	{
		vec2 cameraAspect(screen->getWidth(), screen->getHeight());
		cameraAspect /= cameraAspect.y;
		projection = glm::scale(mat4(),vec3(1 / (zoom * cameraAspect.x / 2) , 1 / zoom , 1));
	}
	return projection * lookAt(transform.GetPosition(), center, transform.GetUp());
}

void Camera::Update(double deltaTime){}
