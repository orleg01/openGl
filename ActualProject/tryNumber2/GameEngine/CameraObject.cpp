#include "CameraObject.h"

CameraObject::CameraObject(Screen * screen):Camera(screen)
{
	AddComponent(this);
}

