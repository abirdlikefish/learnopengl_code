#version 330 core

in vec2 fragmentTextureCoordinate;
in vec3 fragmentPosition;
in vec3 fragmentNormal;

in vec3 pointLightPosition[4];
in vec3 directionalLightDirection[4];
in vec3 spotLightPosition[4];
in vec3 spotLightDirection[4];


struct POINT_LIGHT
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 strength;
};

struct DIRECTIONAL_LIGHT
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 strength;
};

struct SPOT_LIGHT
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 strength;
    float innerCos;
    float outerCos;
};

struct MATERIAL
{
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    float shininess;
};

uniform MATERIAL material;

flat in int pointLightNumber;
flat in int directionalLightNumber;
flat in int spotLightNumber;

uniform POINT_LIGHT pointLight[4];
uniform DIRECTIONAL_LIGHT directionalLight[4];
uniform SPOT_LIGHT spotLight[4];

out vec4 FragColor;

vec3 setPointLight(POINT_LIGHT pointLight , vec3 normal , vec3 eyeDirection , vec3 lightDirection , float distance);

vec3 setDirectionalLight(DIRECTIONAL_LIGHT directionalLight , vec3 normal , vec3 eyeDirection , vec3 lightDirection);

vec3 setSpotLight(SPOT_LIGHT spotLight , vec3 spotLightDirection , vec3 normal , vec3 eyeDirection , vec3 lightDirection , float distance);

void main()
{
    FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec3 normal = normalize(fragmentNormal);
    vec3 eyeDirection = -normalize(fragmentPosition);

    for(int i = 0 ; i < pointLightNumber ; i ++)
    {
        vec3 lightDirection = pointLightPosition[i] - fragmentPosition;

        float distance = length(lightDirection);
        lightDirection = normalize(lightDirection);
        FragColor += vec4( setPointLight(pointLight[i], normal , eyeDirection ,lightDirection , distance) , 1 );
    }

    for(int i = 0 ; i < directionalLightNumber ; i ++)
    {
        vec3 direction = -normalize(directionalLightDirection[i]);
        FragColor += vec4( setDirectionalLight(directionalLight[i], normal , eyeDirection ,direction) , 1 );
    }

    for(int i = 0 ; i < spotLightNumber ; i ++)
    {
        // vec3 lightDirection = spotLightPosition[i] - fragmentPosition;
        vec3 lightDirection =  - fragmentPosition;

        float distance = length(lightDirection);
        lightDirection = normalize(lightDirection);
        FragColor += vec4( setSpotLight(spotLight[i], normalize(spotLightDirection[i]) , normal , eyeDirection ,lightDirection , distance) , 1 );
        // FragColor = vec4( setSpotLight(spotLight[i], normalize(spotLightDirection[i]) , normal , eyeDirection ,lightDirection , distance) , 1 );
    }

}

vec3 setPointLight(POINT_LIGHT pointLight , vec3 normal , vec3 eyeDirection , vec3 lightDirection , float distance)
{
    vec3 ambient = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * pointLight.ambient;
    vec3 diffuse = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * pointLight.diffuse * max(0,dot(normal , lightDirection));
    vec3 specular = texture(material.specularTexture , fragmentTextureCoordinate).xyz * pointLight.specular * pow( max(0,dot(normalize(lightDirection + eyeDirection),normal) ), material.shininess);
    return (ambient + (diffuse + specular) / ( distance * distance + 1 ) ) * pointLight.strength ;
}

vec3 setDirectionalLight(DIRECTIONAL_LIGHT directionalLight , vec3 normal , vec3 eyeDirection , vec3 lightDirection)
{
    vec3 ambient = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * directionalLight.ambient;
    vec3 diffuse = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * directionalLight.diffuse * max(0,dot(normal , lightDirection));
    vec3 specular = texture(material.specularTexture , fragmentTextureCoordinate).xyz * directionalLight.specular * pow( max(0,dot(normalize(lightDirection + eyeDirection),normal) ), material.shininess);
    return (ambient + diffuse + specular) * directionalLight.strength ;
}

vec3 setSpotLight(SPOT_LIGHT spotLight , vec3 spotLightDirection , vec3 normal , vec3 eyeDirection , vec3 lightDirection , float distance)
{
    float factor = (dot(-spotLightDirection , lightDirection) - spotLight.outerCos) / (spotLight.innerCos - spotLight.outerCos) ;
    if(factor < 0)
        return vec3(0,0,0) ;
    else if(factor > 1)
        factor = 1;
    
    vec3 ambient = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * spotLight.ambient;
    vec3 diffuse = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * spotLight.diffuse * max(0,dot(normal , lightDirection));
    vec3 specular = texture(material.specularTexture , fragmentTextureCoordinate).xyz * spotLight.specular * pow( max(0,dot(normalize(lightDirection + eyeDirection),normal) ), material.shininess);
    return (ambient + (diffuse + specular) / ( distance * distance + 1 ) ) * spotLight.strength * factor ;
}
