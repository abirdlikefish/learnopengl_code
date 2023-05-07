#version 330 core

in vec2 fragmentTextureCoordinate;
in vec3 fragmentPosition;
in vec3 fragmentNormal;

in vec3 pointLightPosition[4];

struct POINT_LIGHT
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 strength;
};

struct MATERIAL
{
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    float shininess;
};

uniform MATERIAL material;

uniform POINT_LIGHT pointLight[4];

out vec4 FragColor;

vec3 setPointLight(POINT_LIGHT pointLight , vec3 normal , vec3 eyeDirection , vec3 lightDirection , float distance);

void main()
{
    vec3 normal = normalize(fragmentNormal);
    vec3 eyeDirection = -normalize(fragmentPosition);
/*
    for(int i = 0 ; i < 4 ; i ++)
    {
        vec3 lightDirection = pointLightPosition[i] - fragmentPosition;
        // vec3 lightDirection = fragmentPosition;//

        float distance = length(lightDirection);
        lightDirection = normalize(lightDirection);
        FragColor += vec4( setPointLight(pointLight[i], normal , eyeDirection ,lightDirection , distance) , 1 );
    }
*/

    // vec3 midNormal = normalize(fragmentNormal);
    // float deltaAngle_specular =dot( normalize( normalize(-fragmentPosition ) + normalize(lightPosition_v - fragmentPosition) ) , midNormal );
    // deltaAngle_specular = max( 0 , deltaAngle_specular ) ;

    // float deltaAngle_diffuse = dot(normalize(lightPosition_v - fragmentPosition) , midNormal );
    // deltaAngle_diffuse = max( 0 , deltaAngle_diffuse) ;
    
    // float length_diffuse = length(lightPosition_v - fragmentPosition);

    // vec3 ambient = texture(material.diffuseTexture , fragmentTexture ).xyz * light.ambient;
    // vec3 diffuse = texture(material.diffuseTexture , fragmentTexture ).xyz * light.diffuse * deltaAngle_diffuse / length_diffuse / length_diffuse;
    // vec3 specular = texture(material.specularTexture , fragmentTexture ).xyz * light.specular * pow(deltaAngle_specular , material.shininess) / length_diffuse / length_diffuse;
    // FragColor = vec4( (ambient + diffuse + specular) * lightStrength , 1 );

}

vec3 setPointLight(POINT_LIGHT pointLight , vec3 normal , vec3 eyeDirection , vec3 lightDirection , float distance)
{
    vec3 ambient = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * pointLight.ambient;
    vec3 diffuse = texture(material.diffuseTexture , fragmentTextureCoordinate).xyz * pointLight.diffuse * dot(normal , lightDirection);
    vec3 specular = texture(material.specularTexture , fragmentTextureCoordinate).xyz * pointLight.specular * pow( dot(normalize(lightDirection + eyeDirection),normal) , material.shininess);
    return ambient + (diffuse + specular) / distance / distance  ;
    // return vec3(1,1,1);
}
