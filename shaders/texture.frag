#version 330 core

// Output
out vec4 FragColor;

// Input
in VS_OUT
{
	vec3 FragPos;
    vec2 TexCoords;
} Out;

uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, Out.TexCoords);
}