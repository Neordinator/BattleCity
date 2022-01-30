// СТОРОННИЕ
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>


// ИЗ КОРОБКИ
#include <iostream>
#include <chrono>

// СОБСТВЕННЫЕ
#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Game/Game.h"


glm::ivec2 g_windowSize(640, 480);
Game gBattleCity(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	g_windowSize.x = width;
	g_windowSize.y = height;
	Render::Renderer::setViewport(g_windowSize.x, g_windowSize.y, 0, 0);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		++gBattleCity.stateSwitcher;
		if (gBattleCity.stateSwitcher > 9)
		{
			gBattleCity.stateSwitcher ^= gBattleCity.stateSwitcher;
		}
		switch (gBattleCity.stateSwitcher)
		{
		case 0:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("normalState");
			break;
		case 1:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("hurtState");
			break;
		case 2:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("victoryState");
			break;
		case 3:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("afraidState");
			break;
		case 4:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("sadState");
			break;
		case 5:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("angryState");
			break;
		case 6:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("depressedState");
			break;
		case 7:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("enragedState");
			break;
		case 8:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("happyState");
			break;
		case 9:
			gBattleCity.pAnimeGirlAnimatedSprite->setState("ecstaticState");
			break;
		}
	}
	gBattleCity.setKey(key, action);
}

int main(int argc, char** argv)
{
	// Initialize the Library
	if (!glfwInit())
	{
		std::cout << "glfwInit failed!" << std::endl;
		return -1;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Void 0.01", nullptr, nullptr);
	if (!pWindow)
	{
		std::cout << "glfwCreateWindow failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);

	// Make the window's context current
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGL())
	{
		std::cout << "Can not load GLAD!" << std::endl;
	}
	std::cout << "Render: " << Render::Renderer::getRendererStr() << std::endl;
	std::cout << "OpenGL version: " << Render::Renderer::getVersionStr() << std::endl;

	Render::Renderer::setClearColor(0, 0, 0, 1);

	{
		ResourceManager::setExecutablePath(argv[0]);
		gBattleCity.init();
		

		auto lastTime = std::chrono::high_resolution_clock::now();
		// Loop until the user closes the window
		while (!glfwWindowShouldClose(pWindow))
		{
			// Poll for and process events
			glfwPollEvents();

			auto currentTime = std::chrono::high_resolution_clock::now();
			uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
			lastTime = currentTime;
			//pBattleCityAnimatedSprite->update(duration);
			//pAnimeGirlAnimatedSprite->update(duration);
			gBattleCity.update(duration);
			// Render here
			Render::Renderer::clear();

			//pDefaultShaderProgram->use();
			//glBindVertexArray(vao);
			//tex->bind();

			//pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
			//glDrawArrays(GL_TRIANGLES, 0, 3);

			//pBattleCitySprite->render();
			//pBattleCityAnimatedSprite->render();
			//pAnimeGirlAnimatedSprite->render();
			gBattleCity.render();

			// Swap front and back buffers
			glfwSwapBuffers(pWindow);
		}
		ResourceManager::unloadAllResources();
	}//область видимости для вызова деструктора ResourceManager перед уничтожением контекста OpenGL
	glfwTerminate();
	return 0;
}
