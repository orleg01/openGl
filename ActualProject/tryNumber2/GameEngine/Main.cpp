#include <vector>
#include <glew\GL\glew.h>
#include <glfw\GLFW\glfw3.h>
#include <glm\glm.hpp>

//my Header
#include "Screen.h"
#include "Object.h"
#include "CameraObject.h"
#include "Camera.h"
#include "Mesh.h"
#include "Events.h"

void UpdateFunctionsMutaFuka(Object* obj , float deltaTime , Screen* screen);

static glm::vec2 lasMousePos;

int main() 
{
	double lastFrameTime;
	double deltaTime;
	Screen screen(500 , 500 , "myArray");
	//screen.SetFullScreen(true);
	screen.CreateWindow();
	CameraObject cameraObj(&screen);
	cameraObj.SetViewPort(vec2(0), vec2(1));
	cameraObj.GetTransform().SetPosition(vec3(0,0,-7));
	cameraObj.SetPerspective();
	Mesh mesh(CUBE);
	Object obj(&mesh);
	obj.buildShader();
	std::vector<Object*> vecObj(1 , &obj);
	lastFrameTime = glfwGetTime();
	screen.setMousePos();
	screen.GetMousePosition(&lasMousePos);
	//screen.SetMouseDisable(false);
	while (1)
	{
		double thisTime = glfwGetTime();
		deltaTime = thisTime - lastFrameTime;
		lastFrameTime = thisTime;

		UpdateFunctionsMutaFuka(&cameraObj , deltaTime , &screen);

		glfwPollEvents();
		cameraObj.Renderer(&vecObj);
		screen.Update();
	}

	return 0;
}

static GLfloat yaw2 = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
static GLfloat pitch2 = 0.0f;

void UpdateFunctionsMutaFuka(Object* obj , float deltaTime , Screen* screen)
{
	vec2 mousePos;
	screen->GetMousePosition(&mousePos);

	Transform& transOfObj = obj->GetTransform();

	if (screen->GetKeyPressed(GLFW_KEY_W))
	{
		obj->GetTransform().Translate(transOfObj.GetForward() * deltaTime);
	}
	if (screen->GetKeyPressed(GLFW_KEY_S))
	{
		obj->GetTransform().Translate(transOfObj.GetForward()* -deltaTime);
	}
	if (screen->GetKeyPressed(GLFW_KEY_A))
	{
		obj->GetTransform().Translate(transOfObj.GetRight() * deltaTime);
	}
	if (screen->GetKeyPressed(GLFW_KEY_D))
	{
		obj->GetTransform().Translate(transOfObj.GetRight() * -deltaTime);
	}
	if (screen->GetKeyPressed(GLFW_KEY_SPACE))
	{
		obj->GetTransform().Translate(transOfObj.GetUp()* deltaTime);
	}
	if (screen->GetKeyPressed(GLFW_KEY_TAB))
	{
		obj->GetTransform().Translate(transOfObj.GetUp()* -deltaTime);
	}

	vec2 result = mousePos - lasMousePos;
	// Reversed since y-coordinates go from bottom to left
	lasMousePos = mousePos;

	result *= deltaTime*5;

	yaw2 += result.x;
	pitch2 += result.y;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch2 > 89.0f)
		pitch2 = 89.0f;
	if (pitch2 < -89.0f)
		pitch2 = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw2)) * cos(glm::radians(pitch2));
	front.y = sin(glm::radians(pitch2));
	front.z = sin(glm::radians(yaw2)) * cos(glm::radians(pitch2));
	obj->GetTransform().LookAt( glm::normalize(front));

	lasMousePos = mousePos;
	if (mousePos.y > screen->getHeight() - 5 && result.y > 0)
	{
		lasMousePos.y = mousePos.y = 0;
		screen->setMousePos(mousePos.x, 0);
	}
	if (mousePos.x > screen->getWidth() - 5 && result.x > 0)
	{
		lasMousePos.x = mousePos.x = 0;
		screen->setMousePos(0, mousePos.y);
	}
	if (mousePos.y < 5 && result.y < 0)
	{
		lasMousePos.y = mousePos.y = screen->getHeight();
		screen->setMousePos(mousePos.x, screen->getHeight());
	}
	if (mousePos.x < 5 && result.x < 0)
	{
		lasMousePos.x = mousePos.x = 0;
		screen->setMousePos(screen->getWidth(), mousePos.y);
	}
	
}