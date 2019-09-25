#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // the texture coordinates have attribute position 1

out vec2 ourTextureCoord; // output a texture position

// The model, view, and projection
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
	ourTextureCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
}
