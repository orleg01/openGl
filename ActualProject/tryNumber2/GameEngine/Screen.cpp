#include "Screen.h"

//find the screen and return if not find
#define FIND_SCREEN_OR_NOT(A) int i = findScreen(A);if (i == -1)return;Screen* screen = Screen::allScreens[i];

vector<Screen*> Screen::allScreens;

int findScreen(GLFWwindow* window)
{
	int index = 0;
	for (Screen* selectedScreen : Screen::allScreens)
	{
		if (selectedScreen->window == window)
		{
			return index;
		}
		index++;
	}
	return -1;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	FIND_SCREEN_OR_NOT(window);
	screen->activeKeyEvents(key, scancode, action);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	FIND_SCREEN_OR_NOT(window);
	screen->scrollerDelta = vec2(xoffset, yoffset);
	screen->activeScrollEvents();
}

void window_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	FIND_SCREEN_OR_NOT(window);
	screen->mouse_pressed[button] = action != 0;
	screen->activeMouseClickEvents(button, action);
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	FIND_SCREEN_OR_NOT(window);
	screen->mouse_in_window = entered != 0;
}

void window_mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	FIND_SCREEN_OR_NOT(window);
	screen->mouse_position = vec2(xpos, ypos);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	FIND_SCREEN_OR_NOT(window);
	int p_width, p_height;
	glfwGetFramebufferSize(window, &p_width, &p_height);
	screen->width = p_width;
	screen->height = p_height;
}

Screen::Screen(int width, int height , bool resizeable , string title)
{
	this->width = width;
	this->height = height;
	this->resizeable = resizeable;

	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizeable?GL_TRUE:GL_FALSE);

	this->title = title;
}

Screen::Screen(int width, int height, string title) :Screen(width, height, true, title) {}

bool Screen::shouldBeClosed()
{
	return glfwWindowShouldClose(window) != 0;
}

Screen::~Screen()
{
	//glfwDestroyWindow(window);
}

void Screen::Update()
{
	glfwSwapBuffers(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Screen::GetMouseButton(int button)
{
	if (button < 0 || button > 2)
		return false;
	return mouse_pressed[button];
}

bool Screen::GetKeyPressed(GLuint key)
{
	return glfwGetKey(window, key) != 0;
}

bool Screen::GetMousePosition(vec2* mouse_position)
{
	*mouse_position = this->mouse_position;
	return mouse_in_window;
}

void Screen::SetResizeable(bool resizeable)
{
	if (window != nullptr)
		return;
	glfwWindowHint(GLFW_RESIZABLE, resizeable ? GL_TRUE : GL_FALSE);
	this->resizeable = resizeable;
}

bool Screen::GetResizeable()
{
	return resizeable;
}

void Screen::SetAlwaysOnTop(bool alwaysOnTop)
{
	if (window != nullptr)
		return;
	this->alwaysOnTop = alwaysOnTop;
	glfwWindowHint(GLFW_FLOATING, alwaysOnTop ? GL_TRUE : GL_FALSE);
}

bool Screen::GetAlwaysOnTop()
{
	return alwaysOnTop;
}

void Screen::SetWindowSize(GLuint width, GLuint height)
{
	this->width = width;
	this->height = height;
	glfwSetWindowSize(window, width, height);
}

void Screen::SetPosition(vec2 position)
{
	if (window == nullptr)
		return;
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	position.x *= (mode->width - width) / 2;
	position.y *= (mode->height - height) / 2;
	position += vec2(mode->width / 2, mode->height / 2);
	position -= vec2(width / 2, height / 2);
	glfwSetWindowPos(window, (int)position.x, (int)position.y);
}

void Screen::SetFullScreen(bool fullScreen)
{
	if (window != nullptr)
		return;
	this->fullScreen = fullScreen;
}

bool Screen::GetFullScreen()
{
	return fullScreen;
}

void Screen::CreateWindow()
{
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, title.c_str(), fullScreen?glfwGetPrimaryMonitor():nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		throw "Failed to create GLFW window";
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		throw "Failed to initialize GLEW";
	}

	// Define the viewport dimensions
	glViewport(0, 0, width, height);

	//Define the the color of the default backgraud
	glClearColor(0, 0, 0, 0);

	//Set all the callbacks
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetMouseButtonCallback(window, window_mouse_button_callback);
	glfwSetCursorPosCallback(window, window_mouse_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	//Add to static vector of screen pointers
	allScreens.push_back(this);

	SetPosition(vec2());
}

void Screen::AddMouseClickEvent(MouseClickEvent * mouseClickEvent)
{
	mouseClickEvents.push_back(mouseClickEvent);
}

void Screen::RemoveMouseClickEvent(MouseClickEvent * mouseClickEvent)
{
	REMOVE_FROM_VECTOR_BY_ELEMENT(mouseClickEvents, mouseClickEvent);
}

void Screen::AddScrollEvent(ScrollEvent * scrollEvent)
{
	scrollEvents.push_back(scrollEvent);
}

void Screen::RemoveScrollEvent(ScrollEvent * scrollEvent)
{
	REMOVE_FROM_VECTOR_BY_ELEMENT(scrollEvents, scrollEvent);
}

void Screen::AddKeyEvent(KeyEvent * keyEvent)
{
	keyEvents.push_back(keyEvent);
}

void Screen::RemoveKeyEvent(KeyEvent * keyEvent)
{
	REMOVE_FROM_VECTOR_BY_ELEMENT(keyEvents, keyEvent);
}

void Screen::SetMouseVisible(bool visible)
{
	glfwSetInputMode(window, GLFW_CURSOR, visible?GLFW_CURSOR_NORMAL:GLFW_CURSOR_HIDDEN);
	mouseVisible = visible;
}

void Screen::SetMouseDisable(bool disable)
{
	glfwSetInputMode(window, GLFW_CURSOR, disable ? mouseVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN : GLFW_CURSOR_DISABLED);
}

void Screen::setMousePos(int x, int y)
{
	if (x < 0 && y < 0)
	{
		x = width / 2;
		y = height / 2;
	}
	glfwSetCursorPos(this->window, x, y);
}

void Screen::activeMouseClickEvents(int button, int action)
{
	for (MouseClickEvent* mouseClickEvent : mouseClickEvents)
	{
		mouseClickEvent->click(button, action);
	}
}

void Screen::activeScrollEvents()
{
	for (ScrollEvent* scrollEvent : scrollEvents)
	{
		scrollEvent->scrolled(scrollerDelta);
	}
}

void Screen::activeKeyEvents(int key, int scancode, int action)
{
	for (KeyEvent* keyEvent : keyEvents)
		keyEvent->key(key, scancode, action);
}
