// ImageTest.cpp
//
// Simple image test, tutorial 1 from
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

#include <iostream>

#include <glad/glad.h> // Must be included before glfw3
#include <GLFW/glfw3.h>

// Set some global variables
namespace {
	// Screen height and width
	constexpr int ScreenWidth { 800 };
	constexpr int ScreenHeight { 600 };

	// Vertex and fragment shaders
	const auto shaderSourceVertex {
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0"
	};
	const auto shaderSourceFragment {
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0"
	};
} // anonymous namespace

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
			std::cout << "unknown key (" << key << ")" << std::endl;
			break;
		}
	}
}

// Callback function for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Process user input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	// Error-checking variables
	int success;
	char info[513];

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

	// Make sure GLAD loads
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set the coordinates of the window
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	// Set some callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// Calculate this triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// Create the Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// Use the vertex shader
	unsigned int vertexShader { glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &shaderSourceVertex, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, info);
		std::cout << "Failed to initialize shader: " << info << "\n";
		return EXIT_FAILURE;
	}

	// Use the fragment shader
	unsigned int fragmentShader { glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &shaderSourceFragment, nullptr);
	glCompileShader(fragmentShader);

	// Actually create the shader program
	unsigned int shaderProgram { glCreateProgram() };
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
		std::cout << "Failed to create shader program: " << info << "\n";
		return EXIT_FAILURE;
	}

	// Start with no blue
	auto colorBlue = 0.0f;
	while(!glfwWindowShouldClose(window))
	{
		// Handle keypresses
		processInput(window);

		// Set the clear color, with cycling blue
		glClearColor(0.2f, 0.3f, colorBlue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the buffer in, and poll for events
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Increment blue
		colorBlue += 0.01f;
		if (colorBlue > 1.0f)
		{
			colorBlue = 0.0f;
		}
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
