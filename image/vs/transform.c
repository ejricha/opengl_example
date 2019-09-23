#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord; // the texture coordinates have attribute position 1

out vec2 ourTextureCoord; // output a texture position

uniform mat4 transform; // The 4x4 transformation matrix to apply

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
	ourTextureCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
}
