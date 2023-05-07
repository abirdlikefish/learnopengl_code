#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexture;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoordinate;
out vec3 pointLightPosition[4];


uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec3 pointLight_world[4];

void main()
{
    gl_Position = p * v * m * vec4(vertexPosition , 1 );

    vec4 midVector = v * m * vec4(vertexPosition , 1 ) ;
    fragmentPosition = (midVector / midVector.w ).xyz ;

    fragmentNormal = vec3(v * m * vec4(vertexNormal , 0 ) );

    fragmentTextureCoordinate = vertexTexture;

    for(int i = 0; i < 4; i++)
    {
        midVector = v * vec4(pointLight_world[i] , 1 ) ;
        pointLightPosition[i] = (midVector / midVector.w ).xyz ;
    }
}