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
    glm::vec3 position ;
    glm::vec3 ambient ;
    glm::vec3 diffuse ;
    glm::vec3 specular ;
    glm::vec3 strength ;
public:
    void use(SHADER *shader , int index);
    POINT_LIGHT(glm::vec3 position, glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specular , glm::vec3 strength);
};
POINT_LIGHT::POINT_LIGHT(glm::vec3 position, glm::vec3 ambient = glm::vec3(0.005,0.005,0.005) , glm::vec3 diffuse = glm::vec3(0.5,0.5,0.5) , glm::vec3 specular = glm::vec3(1,1,1) , glm::vec3 strength = glm::vec3(30,30,30))
{
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->strength = strength;
}

void POINT_LIGHT::use(SHADER *shader , int index)
{
    shader -> setAmbientFactor(ambient , index);
    shader -> setDiffuseFactor(diffuse , index);
    shader -> setSpecularFactor(specular , index);
    shader -> setLightPosition(position , index);
    shader -> setLightStrength(strength , index);
}

#endif

