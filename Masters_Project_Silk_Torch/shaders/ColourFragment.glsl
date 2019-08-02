#version 430 core

in vec3 vertColour;
/// @brief The output fragment colour
layout (location =0)out vec4 fragColour;

void main ()
{
    fragColour.rgb=vertColour;
}

