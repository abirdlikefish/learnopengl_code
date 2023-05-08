#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.hpp"

class SPOT_LIGHT
{
private:
    int spotLightNumber;
    glm::vec3 position[4] ;
    glm::vec3 direction[4] ;
    float cutoff[4];
    float outerCutoff[4];
    glm::vec3 ambient[4] ;
    glm::vec3 diffuse[4] ;
    glm::vec3 specular[4] ;
    glm::vec3 strength[4] ;
public:
    void use(SHADER *shader);
    void setSpotLight(int index , glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff, glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specular , glm::vec3 strength);
    SPOT_LIGHT(int number);
};
SPOT_LIGHT::SPOT_LIGHT(int number)
{
    this -> spotLightNumber = number;
}
// void SPOT_LIGHT::setSpotLight(int index , glm::vec3 position, glm::vec3 direction, float cutoff = 0, float outerCutoff = 3, glm::vec3 ambient = glm::vec3(0.002,0.002,0.002) , glm::vec3 diffuse = glm::vec3(0.5,0.5,0.5) , glm::vec3 specular = glm::vec3(1,1,1) , glm::vec3 strength = glm::vec3(5,5,5))
void SPOT_LIGHT::setSpotLight(int index , glm::vec3 position, glm::vec3 direction, float cutoff = 10, float outerCutoff = 20, glm::vec3 ambient = glm::vec3(0.002,0.002,0.002) , glm::vec3 diffuse = glm::vec3(0.5,0.5,0.5) , glm::vec3 specular = glm::vec3(1,1,1) , glm::vec3 strength = glm::vec3(5,5,5))
{
    this->position[index] = position;
    this->direction[index] = direction;
    this->outerCutoff[index] = outerCutoff;
    this->cutoff[index] = cutoff;
    this->ambient[index] = ambient;
    this->diffuse[index] = diffuse;
    this->specular[index] = specular;
    this->strength[index] = strength;
}

void SPOT_LIGHT::use(SHADER *shader)
{
    shader -> setSpotLightNumber(spotLightNumber);
    for(int i = 0; i < spotLightNumber ; i++)
    {
        shader -> setAmbientFactor_spotLight(ambient[i] , i);
        shader -> setDiffuseFactor_spotLight(diffuse[i] , i);
        shader -> setSpecularFactor_spotLight(specular[i] , i);
        shader -> setSpotLightPosition(position[i] , i);
        shader -> setSpotLightStrength(strength[i] , i);
        shader -> setSpotLightDirection(direction[i] , i);
        shader -> setCutoff_cos(cos(glm::radians(cutoff[i])) , i);
        shader -> setOuterCutoff_cos(cos(glm::radians(outerCutoff[i])) , i);
        std::cout << cutoff[i] << " " << outerCutoff[i] << std::endl;
    }
}

#endif

