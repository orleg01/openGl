#pragma once
#include <iostream>

#include <glew\GL\glew.h>
#include <glfw\GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>
#include <unordered_map>

#include "Events.h"
#include "Macros.h"

using namespace std;
using namespace glm;

class Screen
{
public:
	Screen(int width, int height, bool resizeable , string title);
	Screen(int width, int height, string title);

	bool shouldBeClosed();
	~Screen();
	void Update();
	
	/**
	return if the button mouse is current pressed
	0:left , 1:right , 2:middel
	*/
	bool GetMouseButton(int button);

	/**
	return if button pressed
	key most be enum like:
	v:GLFW_KEY_V , k:GLFW_KEY_K ,...
	*/
	bool GetKeyPressed(GLuint key);

	/**
	return if the mouse inside the window and set 
	mouse_position the position of the mouse
	*/
	bool GetMousePosition(vec2* mouse_position);

	/** 
	set if the is the screen resizeable 
	note :work until the screen get created
	*/
	void SetResizeable(bool resizeable);
	bool GetResizeable();

	/**
	set if the is the screen is allways on top
	note :work until the screen get created
	*/
	void SetAlwaysOnTop(bool alwaysOnTop);
	bool GetAlwaysOnTop();

	void SetWindowSize(GLuint width, GLuint height);

	/**
	set the position of the screen 
	0,0 - in the center
	1,1 - right down corner
	-1,-1 - left top corner
	*/
	void SetPosition(vec2 position);

	/**
	set if full screen
	note :can be changed until window creation
	*/
	void SetFullScreen(bool fullScreen);
	bool GetFullScreen();

	void CreateWindow();

	//set and remove all the Events
	void AddMouseClickEvent(MouseClickEvent* mouseClickEvent);
	void RemoveMouseClickEvent(MouseClickEvent* mouseClickEvent);

	void AddScrollEvent(ScrollEvent * scrollEvent);
	void RemoveScrollEvent(ScrollEvent* scrollEvent);

	void AddKeyEvent(KeyEvent* keyEvent);
	void RemoveKeyEvent(KeyEvent* keyEvent);

	void SetMouseVisible(bool visible);
	void SetMouseDisable(bool disable);

	inline GLuint getWidth() { return width; }
	inline GLuint getHeight() { return height; }
	
	// -5 for middle ofScreen
	void setMousePos(int x = -5, int y = -5);

private:
	friend int findScreen(GLFWwindow* window);
	friend void window_size_callback(GLFWwindow* window, int width, int height);
	
	friend void window_mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend void window_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend void cursor_enter_callback(GLFWwindow* window, int entered);
	friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	//active all action events
	void activeMouseClickEvents(int button, int action);
	void activeScrollEvents();
	void activeKeyEvents(int key, int scancode, int action);

	//mouse inputs
	bool mouse_in_window;
	bool mouse_pressed[3] = { false , false , false };
	vec2 mouse_position;
	vec2 scrollerDelta;
	
	string title;
	bool resizeable = true;
	bool alwaysOnTop = false;
	bool mouseVisible = true;
	bool fullScreen = false;

	vector<MouseClickEvent*> mouseClickEvents;
	vector<ScrollEvent*> scrollEvents;
	vector<KeyEvent*> keyEvents;

	GLFWwindow* window = nullptr;
	GLuint width, height;
	static vector<Screen*> allScreens;
};

