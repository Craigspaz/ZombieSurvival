#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <cstring>
#include "Game.h"
#include <SOIL.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int main(int argc, char** argv)
{
	
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	int width = 1366;
	int height = 768;
	std::ifstream file("settings.txt");
	if (file.is_open())
	{
		std::string line;
		int l = 0;
		while (std::getline(file, line))
		{
			if (l == 0)
			{
				width = std::stoi(line);
			}
			if (l == 1)
			{
				height = std::stoi(line);
			}
			l++;
		}
	}
	file.close();
	const std::string VERSION = "2.1.3";
	std::ofstream ver;
	ver.open("version.txt");
	ver << VERSION << std::endl;
	ver.close();
	const std::string TITLE = ("Survival " + VERSION);
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	std::cout << "There are : " << monitorCount << " monitors.\n";

	//fullscreen settings
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_SAMPLES, (8 + mode->redBits + mode->greenBits + mode->blueBits));
	GLFWwindow* window = glfwCreateWindow(width, height, TITLE.c_str(), primary, NULL);
	//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, TITLE.c_str(), primary, NULL);
	//Development Window below
	//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, TITLE.c_str(), NULL, NULL);
	
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glewInit();
	double lastTime = glfwGetTime();
	double deltaTime = 0.0f;
	GLFWimage image;
	int w, h;
	int channels;
	unsigned char* p = new unsigned char[16 * 16 * 4];
	memset(p, 0xff,sizeof(p));
	p = SOIL_load_image("res/cursor.dds",&w,&h,&channels,SOIL_LOAD_RGBA);
	image.width = w;
	image.height = h;
	image.pixels = p;
	GLFWcursor* cursor = glfwCreateCursor(&image,0,0);
	glfwSetCursor(window,cursor);
#define Updates_Per_Second 60.0f

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Objects
	Game* game = new Game(width,height);

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		ratio = w / (float)h;
		glViewport(0, 0, w, h);

		double currentTime = glfwGetTime();
		deltaTime += (currentTime - lastTime) * Updates_Per_Second;
		lastTime = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		while (deltaTime >= 1.0f / Updates_Per_Second)
		{
			//update
			game->update();
			--deltaTime;
		}
		//render
		game->render();
		glfwSwapBuffers(window);
		//glfwSwapInterval(60);
		glfwPollEvents();
	}
	SOIL_free_image_data(p);
	glfwDestroyCursor(cursor);
	glfwDestroyWindow(window);
	glfwTerminate();
	//system("PAUSE");
	return 0;
}

