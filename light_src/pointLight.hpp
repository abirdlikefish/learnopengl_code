#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.hpp"

class POINT_LIGHT
{
private:
    int pointLightNumber;
    glm::vec3 position[4] ;
    glm::vec3 ambient[4] ;
    glm::vec3 diffuse[4] ;
    glm::vec3 specular[4] ;
    glm::vec3 strength[4] ;
public:
    void use(SHADER *shader);
    void setPointLight(int index , glm::vec3 position, glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specular , glm::vec3 strength);
    POINT_LIGHT(int number);
};
POINT_LIGHT::POINT_LIGHT(int number)
{
    this -> pointLightNumber = number;
}
void POINT_LIGHT::setPointLight(int index , glm::vec3 position, glm::vec3 ambient = glm::vec3(0.002,0.002,0.002) , glm::vec3 diffuse = glm::vec3(0.5,0.5,0.5) , glm::vec3 specular = glm::vec3(1,1,1) , glm::vec3 strength = glm::vec3(10,10,10))
{
    this->position[index] = position;
    this->ambient[index] = ambient;
    this->diffuse[index] = diffuse;
    this->specular[index] = specular;
    this->strength[index] = strength;
}

void POINT_LIGHT::use(SHADER *shader)
{
    shader -> setPointLightNumber(pointLightNumber);
    for(int i = 0; i < pointLightNumber ; i++)
    {
        shader -> setAmbientFactor_pointLight(ambient[i] , i);
        shader -> setDiffuseFactor_pointLight(diffuse[i] , i);
        shader -> setSpecularFactor_pointLight(specular[i] , i);
        shader -> setPointLightPosition(position[i] , i);
        shader -> setPointLightStrength(strength[i] , i);
    }
}

#endif

