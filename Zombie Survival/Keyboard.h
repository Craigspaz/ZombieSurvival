#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <iostream>
#include <GLFW\glfw3.h>
class Keyboard
{
private:
	Keyboard();
	~Keyboard();
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool KEYS[348];
public:
	static Keyboard& getKeyboard();
	static void destroyKeyboard();
	static void keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool getKeyState(int key);
};


#endif