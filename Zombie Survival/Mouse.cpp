#include "Mouse.h"


Mouse::Mouse()
: _x(0), _y(0)
{
	for (int i = 0; i < 12; i++)
	{
		MOUSE[i] = false;
	}
}


Mouse::~Mouse()
{

}

double Mouse::getX()
{
	return _x;
}
double Mouse::getY()
{
	return _y;
}
Mouse& Mouse::getMouse()
{
	static Mouse* mouse = NULL;
	if (mouse == NULL)
	{
		glfwSetCursorPosCallback(glfwGetCurrentContext(), *cursor_position_callbackFun);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), *mouse_button_callbackFun);
		glfwSetScrollCallback(glfwGetCurrentContext(), *scroll_callbackFun);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		mouse = new Mouse();
	}
	return *mouse;
}
void Mouse::destroyMouse()
{
	Mouse* mouse = &getMouse();
	delete mouse;
}
void Mouse::cursor_position_callbackFun(GLFWwindow* window, double x, double y)
{
	Mouse* mouse = &getMouse();
	mouse->cursor_position_callback(window, x, y);
}


void Mouse::cursor_position_callback(GLFWwindow* window, double x, double y)
{
	_x = x;
	_y = y;
}

void Mouse::scroll_callback(GLFWwindow* window, double x, double y)
{

}

void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		MOUSE[button] = true;
		//std::cout << "MOUSE Button Pressed\n";
	}
	else
	{
		MOUSE[button] = false;
		//std::cout << "MOUSE Button RELEASED\n";
	}
}


void Mouse::mouse_button_callbackFun(GLFWwindow* window, int button, int action, int mods)
{
	Mouse* mouse = &getMouse();
	mouse->mouse_button_callback(window, button, action, mods);
}

bool Mouse::getMouseState(int button)
{
	return MOUSE[button];
}

void Mouse::scroll_callbackFun(GLFWwindow* window, double x, double y)
{
	Mouse* mouse = &getMouse();
	mouse->scroll_callback(window,x,y);
}