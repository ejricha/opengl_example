// ImageTest.cpp
//
// Simple image test, tutorial 1 from
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

#include <iostream>

#include <GLFW/glfw3.h>

int main(void)
{
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
	{
		return EXIT_FAILURE;
	}

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	
	// Show the OpenGL version
	std::cout << "OpenGL version is " << glGetString(GL_VERSION) << std::endl;

	// Loop until the user closes the window
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
	return 0;
}
