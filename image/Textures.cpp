// Textures.cpp
//
// Test loading shaders from file
// https://learnopengl.com/Getting-started/Textures

#include <iostream>
#include <cmath>

#include <glad/glad.h> // Must be included before glfw3
#include <GLFW/glfw3.h>

#include "CreateShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	Shader ourShader("vs/texture.c", "fs/texture.c");

	// Texture coordiates
	float vertices[] = {
		// positions      // colors         // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
	};


	// Choose how to wrap textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE);
	//float borderColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
	//glTexParameterv(GL_TEXTURE_2D, GL_CLAMP_TO_BORDER, borderColor);

	// Choose how to filter textures
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// GL_(NEAREST|LINEAR)_MIPMAP_(NEAREST|LINEAR)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	// Load the image of a wooden container
	int width, height, nrChannels;
	const auto imagePath { "/home/eric/software/github/ejricha/opengl_example/image/container.jpg" };
	unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
	if (data == nullptr)
	{
		std::cout << "Failed to load texture (" << imagePath << ")" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Show the number of vertex attributes supported
	int NumVertexAttributesSupported;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &NumVertexAttributesSupported);
	std::cout << "Number of vertex attributes supported = " << NumVertexAttributesSupported << std::endl;

	// Draw in wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// Use our shader
	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // set it manually
	ourShader.setInt("texture1", 1); // or with shader class

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the background color to dark red
		glClearColor(0.3f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Get the current time
		const auto timeValue = glfwGetTime();
		
		// Move the texture in a circle
		const auto offsetValueX = std::sin(timeValue) / 2.0;
		const auto offsetValueY = std::cos(timeValue) / 2.0;
		ourShader.setFloat("uniformOffsetX", offsetValueX);
		ourShader.setFloat("uniformOffsetY", offsetValueY);

		// Show the texture
		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up buffers
	glDeleteVertexArrays(1, &VAO);

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
