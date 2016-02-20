#ifndef __EVENTS__H
#define __EVENTS__H

#include <glm\glm.hpp>

class ScrollEvent
{
public:
	virtual void scrolled(glm::vec2 offset) = 0;
};

class MouseClickEvent
{
public:
	virtual void click(int button, int action) = 0;
};

class KeyEvent
{
public:
	virtual void key(int key , int scancode, int action) = 0;
};

#endif
