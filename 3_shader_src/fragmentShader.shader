#version 330 core
in vec4 fragmentColor;
out vec4 FragColor;
uniform float colorOffset;

void main()
{
    FragColor = fragmentColor * colorOffset;
}