#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
out vec4 fragmentColor;

void main()
{
    gl_Position = vec4(vertexPosition , 1 );
    fragmentColor = vec4(vertexColor / 2 + 0.5 , 1 );
}