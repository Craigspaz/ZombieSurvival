#ifndef _MOUSE_H
#define _MOUSE_H
#include <iostream>
#include <GLFW\glfw3.h>
class Mouse
{
private:
	Mouse();
	~Mouse();
	void cursor_position_callback(GLFWwindow* window, double x, double y);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double x, double y);
	double _x;
	double _y;
	GLFWimage* image;
	bool MOUSE[12];
public:
	double getX();
	double getY();
	bool getMouseState(int button);
	static Mouse& getMouse();
	static void destroyMouse();
	static void cursor_position_callbackFun(GLFWwindow* window, double x, double y);
	static void mouse_button_callbackFun(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callbackFun(GLFWwindow* window, double x, double y);
};

#endif