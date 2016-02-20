#ifndef __COMPONENT__H
#define __COMPONENT__H

class Object;

class Component
{
public:
	Component();
	friend void SetObject(Component*, Object*);
	virtual void Update(double deltaTime) = 0;

protected:
	Object* object;
};

#endif