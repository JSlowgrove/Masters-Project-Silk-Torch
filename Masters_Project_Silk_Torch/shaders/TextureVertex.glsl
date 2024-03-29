#version 330 core

/// @brief MVP passed from app
uniform mat4 MVP;
// transformation matrix
uniform mat4 transform;
// first attribute the vertex values from our VAO
layout (location=0) in vec3 inVert;
// second attribute the UV values from our VAO
layout (location=2) in vec2 inUV;
// we use this to pass the UV values to the frag shader
out vec2 vertUV;

void main()
{
	// calculate the vertex position
        gl_Position = MVP*transform*vec4(inVert, 1.0);
	// pass the UV values to the frag shader
  vertUV=inUV.st;
}
