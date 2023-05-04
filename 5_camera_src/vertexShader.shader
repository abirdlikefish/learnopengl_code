#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexTexture;

out vec4 fragmentColor;
out vec2 fragmentTexture;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vertexPosition , 1 );
    fragmentColor = vec4(vertexColor / 2 + 0.5 , 1 );
    fragmentTexture = vertexTexture;
}