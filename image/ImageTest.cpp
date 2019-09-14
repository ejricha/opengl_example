// ImageTest.cpp
//
// Simple image test, tutorial 1 from
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

// Callback function for key press
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Handle a few types of key presses
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_Q:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			std::cout << "unknown key (" << key << ")\n";
		}
	}
}

// Main function
int main(int argc, char** argv)
{
	// Initialize the library
	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	// Create a windowed mode window and its OpenGL context
	auto window = glfwCreateWindow(640, 480, "Window created using GLFW", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Show the OpenGL version
	std::cout << "OpenGL version is " << glGetString(GL_VERSION) << std::endl;

	// Set the function for key presses
	glfwSetKeyCallback(window, key_callback);

	// Test GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error, GLEW is not OK!\n";
		return EXIT_FAILURE;
	}

	// Loop until the user closes the window or presses escape
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f( 0.0, +0.5);
		glVertex2f(+0.5, -0.5);
		glEnd();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
