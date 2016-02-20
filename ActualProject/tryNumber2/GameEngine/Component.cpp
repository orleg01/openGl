#include "Component.h"



Component::Component(){}

void SetObject(Component* component, Object* object)
{
	component->object = object;
}
