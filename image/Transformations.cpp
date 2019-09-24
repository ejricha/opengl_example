// Transformations.cpp
//
// Test applying transformations to textures
// https://learnopengl.com/Getting-started/Transformations

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h> // Must be included before glfw3
#include <GLFW/glfw3.h>

#include "CreateShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Movement
#include "Movement.h"

// Set some global variables
namespace {
	// Screen height and width
	constexpr int ScreenWidth { 800 };
	constexpr int ScreenHeight { 600 };
} // anonymous namespace

// Callback function definitions
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Global Movement object
Movement movement;

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
	Shader ourShader("vs/transform.c", "fs/transform.c");

	// Texture coordiates
	float vertices[] = {
	// positions          // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// Tests of GLM
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

	// Confirm the shader path
	std::cout << "TEXTURE_DIR=(" << TEXTURE_DIR << ")\n";

	// Show the number of vertex attributes supported
	int NumVertexAttributesSupported;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &NumVertexAttributesSupported);
	std::cout << "Number of vertex attributes supported = " << NumVertexAttributesSupported << std::endl;

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// load and create a texture
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	const auto Texture1Path = std::filesystem::path(TEXTURE_DIR) / "container.jpg";
	unsigned char* data = stbi_load(Texture1Path.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture\n";
		return EXIT_FAILURE;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// load and create a second texture
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	const auto Texture2Path = std::filesystem::path(TEXTURE_DIR) / "awesomeface.png";
	data = stbi_load(Texture2Path.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture\n";
		return EXIT_FAILURE;
	}
	// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// Draw in wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Initial rotation is 50%
	movement.SetVelocityZ(20);

	double angle { 0.0 };

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Set the background color to dark red
		glClearColor(0.3f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rotate and scale the texture
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(movement.GetVelocityX() / 100.0f, movement.GetVelocityY() / 100.0f, 0.0f));
		transform = glm::rotate(transform, static_cast<float>(angle), glm::vec3(1.0f, 0.2f, 0.4f));

		// Apply the change in angle
		angle -= movement.GetVelocityZ() / (6000.0f / (2 * M_PI));

		// Show both textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Actually render the container
		ourShader.use();
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

// Callback function for key press
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Trigger on key down
	if (action == GLFW_PRESS)
	{
		// Handle modifier keys
		int multiplier = 4;
		if (mods > 0) {
			if ((mods & GLFW_MOD_SHIFT) > 0) {
				multiplier /= 4;
			}
			if ((mods & GLFW_MOD_CONTROL) > 0) {
				multiplier *= 5;
			}
		}

		// Handle the actual keypress
		switch (key)
		{
		// Quit
		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_Q:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		// Move in x direction
		case GLFW_KEY_RIGHT:
		case GLFW_KEY_L:
			movement.IncrementVelocityX(multiplier);
			break;
		case GLFW_KEY_LEFT:
		case GLFW_KEY_H:
			movement.IncrementVelocityX(-multiplier);
			break;
		// Move in y direction
		case GLFW_KEY_UP:
		case GLFW_KEY_K:
			movement.IncrementVelocityY(multiplier);
			break;
		case GLFW_KEY_DOWN:
		case GLFW_KEY_J:
			movement.IncrementVelocityY(-multiplier);
			break;
		// Move in z direction
		case GLFW_KEY_RIGHT_BRACKET:
			movement.IncrementVelocityZ(multiplier);
			break;
		case GLFW_KEY_LEFT_BRACKET:
			movement.IncrementVelocityZ(-multiplier);
			break;
		// Pause all movement
		case GLFW_KEY_SPACE:
			movement.PlayPause();
			break;
		// Unhandled key
		default:
			std::cout << "key was " << key << " * " << multiplier << "\n";
			break;
		}

		// Print movement
		movement.Print();
	}
}

// Callback function for window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
