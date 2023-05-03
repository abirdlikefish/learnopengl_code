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
        // FragColor = mix( texture(texture0 , fragmentTexture ) , texture(texture1 , vec2(1 - fragmentTexture.x , fragmentTexture.y) ) , mixParameter );
        // FragColor = mix( texture(texture0 , fragmentTexture ) , texture(texture1 , fragmentTexture ) , mixParameter );
        FragColor = mix( texture(texture0 , fragmentTexture ) , texture(texture1 , fragmentTexture * 2 ) , mixParameter );
        // FragColor = mix( texture(texture0 , fragmentTexture / 10 ) , texture(texture1 , fragmentTexture * 2 ) , mixParameter );
    }
    else if(textureNumber == 3)
    {
        FragColor = vec4(0,0,0,0);
    }

}