#version 330 core

// Input
layout (location = 0) in vec3 aPos;

// Output
out VS_OUT
{
	vec3 FragPos;
} Out;

// Uniforms
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	Out.FragPos = vec3(uModel * vec4(aPos, 1.0));

	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}