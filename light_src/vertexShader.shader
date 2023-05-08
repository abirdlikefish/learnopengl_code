#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexture;

out vec3 fragmentPosition;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoordinate;
out vec3 pointLightPosition[4];
out vec3 directionalLightDirection[4];
out vec3 spotLightPosition[4];
out vec3 spotLightDirection[4];


uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec3 pointLightPosition_world[4];
uniform vec3 directionalLightDirection_world[4];
uniform vec3 spotLightPosition_world[4];
uniform vec3 spotLightDirection_world[4];

uniform int pointLightNumber_v;
uniform int directionalLightNumber_v;
uniform int spotLightNumber_v;

out int pointLightNumber;
out int directionalLightNumber;
out int spotLightNumber;

void main()
{
    pointLightNumber = pointLightNumber_v;
    directionalLightNumber = directionalLightNumber_v;
    spotLightNumber = spotLightNumber_v;
    
    gl_Position = p * v * m * vec4(vertexPosition , 1 );
    
    vec4 midVector = v * m * vec4(vertexPosition , 1 ) ;
    fragmentPosition = (midVector / midVector.w ).xyz ;

    fragmentNormal = vec3(v * m * vec4(vertexNormal , 0 ) );

    fragmentTextureCoordinate = vertexTexture;

    for(int i = 0; i < pointLightNumber ; i++)
    {
        midVector = v * vec4(pointLightPosition_world[i] , 1 ) ;
        pointLightPosition[i] = (midVector / midVector.w ).xyz ;
    }
    
    for(int i = 0; i < directionalLightNumber ; i++)
    {
        midVector = v * vec4(directionalLightDirection_world[i] , 0.0f ) ;
        directionalLightDirection[i] = midVector.xyz ;
    }

    for(int i = 0; i < spotLightNumber ; i++)
    {
        midVector = v * vec4(spotLightDirection_world[i] , 0.0f ) ;
        spotLightDirection[i] = midVector.xyz ;

        midVector = v * vec4(spotLightPosition_world[i] , 1 ) ;
        spotLightPosition[i] = (midVector / midVector.w ).xyz ;

    }

}