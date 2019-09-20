// Shaders.cpp
//
// Test loading shaders from file
// https://learnopengl.com/Getting-started/Shaders

#include <iostream>
#include <cmath>

#include <glad/glad.h> // Must be included before glfw3
#include <GLFW/glfw3.h>

#include "CreateShader.h"

// Set some global variables
namespace {
	// Screen height and width
	constexpr int ScreenWidth { 800 };
	constexpr int ScreenHeight { 600 };
} // anonymous namespace

// Callback function definitions
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Main function
int main()
{
	// Initialize glfw and set some variables
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(ScreenWidth, ScreenHeight, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	// Set some callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// Make sure GLAD loads
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Build and compile our shader programs
	Shader ourShader("vs/positions_and_colors.c", "fs/simple.c");

	// Configure vertex attributes
	float vertices[]
	{
		// positions		 // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Show how many vertex attributes are supported
	int NumVertexAttributesSupported;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &NumVertexAttributesSupported);
	std::cout << "Number of vertex attributes supported = " << NumVertexAttributesSupported << "\n";

	// Flush the output
	std::cout << std::endl;
	
	// Draw in wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// Start with no blue
	auto colorBlue = 0.0f;
	double delta = 0.01;

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the clear color, with cycling blue
		glClearColor(0.5f, 0.1f, colorBlue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Use our shader
		ourShader.use();

		// Get the current time
		const auto timeValue = glfwGetTime();

		// Update the amount of green in every vertex
		const auto greenValue = std::sin(timeValue) / 4.0 + 0.4f;
		ourShader.setFloat("uniformGreen", greenValue);

		// Move the triangle in a circle
		const auto offsetValueX = std::sin(timeValue) / 2.0;
		const auto offsetValueY = std::cos(timeValue) / 2.0;
		ourShader.setFloat("uniformOffsetX", offsetValueX);
		ourShader.setFloat("uniformOffsetY", offsetValueY);

		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Increment blue
		colorBlue += delta;
		if ((colorBlue >= 1.0f) || (colorBlue <= 0.0f))
		{
			delta = -delta;
			colorBlue += delta;
		}
	}

	// Clean up buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

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
			break;
		}
	}
}

// Callback function for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
