#version 430 core

/// @brief The vertex passed in
layout(location =0)in vec3 inVert;
/// @brief The normal passed in
layout(location =1)in vec3 inColour;

uniform mat4 MVP;
out vec3 vertColour;

void main()
{
  // calculate the vertex position
  gl_Position = MVP*vec4(inVert,1.0);
  vertColour = inColour;
}
