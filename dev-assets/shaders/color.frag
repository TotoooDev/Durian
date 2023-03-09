#version 330 core

// Output
out vec4 FragColor;

// Input
in VS_OUT
{
	vec3 FragPos;
} Out;

uniform vec4 uColor;

void main()
{
	FragColor = uColor;
}