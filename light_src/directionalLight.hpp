#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.hpp"

class DIRECTIONAL_LIGHT
{
private:
    int directionalLightNumber;
    glm::vec3 direction[4] ;
    glm::vec3 ambient[4] ;
    glm::vec3 diffuse[4] ;
    glm::vec3 specular[4] ;
    glm::vec3 strength[4] ;
public:
    void use(SHADER *shader);
    void setDirectionalLight(int index , glm::vec3 directional, glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specular , glm::vec3 strength);
    DIRECTIONAL_LIGHT(int number);

};


DIRECTIONAL_LIGHT::DIRECTIONAL_LIGHT(int number)
{
    this -> directionalLightNumber = number;
}
void DIRECTIONAL_LIGHT::setDirectionalLight(int index , glm::vec3 direction, glm::vec3 ambient = glm::vec3(0.02,0.02,0.02) , glm::vec3 diffuse = glm::vec3(0.5,0.5,0.5) , glm::vec3 specular = glm::vec3(1,1,1) , glm::vec3 strength = glm::vec3(1,1,1))
{
    this->direction[index] = direction;
    this->ambient[index] = ambient;
    this->diffuse[index] = diffuse;
    this->specular[index] = specular;
    this->strength[index] = strength;
}

void DIRECTIONAL_LIGHT::use(SHADER *shader)
{
    shader -> setDirectionalLightNumber(directionalLightNumber);
    for(int i = 0; i < directionalLightNumber ; i++)
    {
        shader -> setAmbientFactor_directionalLight(ambient[i] , i);
        shader -> setDiffuseFactor_directionalLight(diffuse[i] , i);
        shader -> setSpecularFactor_directionalLight(specular[i] , i);
        shader -> setDirectionalLightDirection(direction[i] , i);
        shader -> setDirectionalLightStrength(strength[i] , i);
    }
}

#endif