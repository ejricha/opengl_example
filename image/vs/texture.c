#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture coordinates have attribute position 2

// Set these values in OpenGL code
uniform float uniformGreen; // Amount of green at every vertex
uniform float uniformOffsetX; // Add to horizontal position
uniform float uniformOffsetY; // Add to vertical position

out vec3 ourColor; // output a color to the fragment shader
out vec2 ourTextureCoord; // output a texture position

void main()
{
    gl_Position = vec4(aPos.x + uniformOffsetX, aPos.y + uniformOffsetY, uniformOffsetX, 1.0);
    //ourColor = vec3(aColor.r, uniformGreen, aColor.b); // set ourColor to the input color we got from the vertex data
    ourColor = vec3(aColor.g, aColor.b, aColor.r); // Cycle the amount of red instead
	ourTextureCoord = aTexCoord;
}
