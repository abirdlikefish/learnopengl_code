#version 330 core
in vec4 fragmentColor;
in vec2 fragmentTexture;
out vec4 FragColor;
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int textureNumber;
uniform float mixParameter;


void main()
{
    if(textureNumber == 1)
    {
        FragColor = texture(texture0 , fragmentTexture );
    }
    else if(textureNumber == 2)
    {
        FragColor = mix( texture(texture0 , fragmentTexture ) , texture(texture1 , fragmentTexture ) , 0.7 );
    }
    else if(textureNumber == 3)
    {
        FragColor = vec4(0,0,0,0);
    }
    else
    {
        FragColor = vec4(1,0,0,0);

    }

}