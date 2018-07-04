#include "Keyboard.h"


Keyboard::Keyboard()
{
	for (int i = 0; i < 348; i++)
	{
		KEYS[i] = false;
	}
}


Keyboard::~Keyboard()
{

}

void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
	//	if (GLFW_CURSOR_DISABLED == glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR))
	//	{
	//		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//	}
	//	else
	//	{
	//		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//	}
	//}
	if (action == GLFW_PRESS)
	{
		KEYS[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		KEYS[key] = false;
	}
	else
	{
		KEYS[key] = true;
	}
}

void Keyboard::keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Keyboard* keyboard = &getKeyboard();
	keyboard->keyCallback(window, key, scancode, action, mods);
}

Keyboard& Keyboard::getKeyboard()
{
	static Keyboard* keyboard = NULL;
	if (keyboard == NULL)
	{
		glfwSetKeyCallback(glfwGetCurrentContext(), *keyCallbackFun);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		keyboard = new Keyboard();
	}
	return *keyboard;
}

void Keyboard::destroyKeyboard()
{
	Keyboard* keyboard = &getKeyboard();
	delete keyboard;
}

bool Keyboard::getKeyState(int key)
{
	return KEYS[key];
}
