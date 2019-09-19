// HelloTriangle.cpp
//
// Simple test of drawing a triangle
// https://learnopengl.com/Getting-started/Hello-Triangle

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
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, info);
		std::cout << "Failed to initialize fragment shader: " << info << "\n";
		return EXIT_FAILURE;
    }

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

	// Delete the shaders that we no longer need
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Set the coordinates of the window
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	// Calculate this triangle
	float vertices[] {
		-0.8f, -0.8f, 0.0f,
		-0.8f, -0.6f, 0.0f,
		-0.6f, -0.6f, 0.0f,
		-0.6f, -0.4f, 0.0f,
		-0.4f, -0.4f, 0.0f,
		-0.4f, -0.2f, 0.0f,
		-0.2f, -0.2f, 0.0f,
		-0.2f, -0.0f, 0.0f,
		+0.0f, +0.0f, 0.0f,
		+0.0f, +0.2f, 0.0f,
		+0.2f, +0.2f, 0.0f
	};
	const int NumVertices { 4 };
	unsigned int indices[] { 0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5, 4, 5, 6, 5, 6, 7, 6, 7, 8, 7, 8, 9, 8, 9, 10 };
	const auto NumIndices { (NumVertices - 1) * 3 };

	// Generate some buffers
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, NumVertices, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Draw in wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Start with no blue
	auto colorBlue = 0.0f;
	double delta = 0.01;
	while(!glfwWindowShouldClose(window))
	{
		// Handle keypresses
		processInput(window);

		// Set the clear color, with cycling blue
		glClearColor(0.2f, 0.3f, colorBlue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the specified shader program
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0);

		// Swap the buffer in, and poll for events
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
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}
