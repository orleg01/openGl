#ifndef __CAMERA_OBJECT__H
#define __CAMERA_OBJECT__H

#include "Object.h"
#include "Screen.h"
#include "Camera.h"

class CameraObject : public Object , public Camera
{
public:
	CameraObject(Screen* screen);
private:
};

#endif

