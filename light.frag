#version 330 core

out vec4 FragColor;

uniform vec4 color;

uniform float time;

void main()
{
	FragColor = color;
}