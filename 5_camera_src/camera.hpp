#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class CAMERA
{
private:
    glm::vec4 position;//(x,x,x,1)
    glm::vec4 direction;//(x,x,x,0)
    // glm::vec4 right;//(x,x,x,0)
    float upAngle;
    float leftAngle;

public:
    float fov;
    float zNear;
    float zFar;
    CAMERA(glm::vec3 position, glm::vec3 direction,float fov,float zNear,float zFar );
    void moveForward(float length);
    void moveRight(float length);
    void rotateUp(float angle);
    void rotateLeft(float angle);
    glm::vec4 getDirection();
    glm::vec4 getRight();
    glm::vec3 getPosition();

};
CAMERA::CAMERA(glm::vec3 position, glm::vec3 direction,float fov = 45 ,float zNear = 0.1 ,float zFar = 100 )
{
    this -> position = glm::vec4(position , 1);
    this -> direction = glm::vec4(direction , 0);
    this -> fov = fov;
    this -> zNear = zNear ;
    this -> zFar = zFar;
}
void CAMERA::moveForward(float length)
{
    position += length * getDirection();
}

void CAMERA::moveRight(float length)
{
    position += length * getRight();
}

void CAMERA::rotateUp(float angle)
{
    upAngle += angle ;
    if(upAngle > 89 )
        upAngle = 89;
    if(upAngle < -89 )
        upAngle = -89;
    // std::cout << upAngle << std::endl;
}
void CAMERA::rotateLeft(float angle)
{
    leftAngle += angle;
    if(leftAngle > 360 )
        leftAngle -= 360;
    if(leftAngle < -360 )
        leftAngle += 360;
}
glm::vec4 CAMERA::getDirection()
{
    glm::mat4 midMatrix = glm::rotate(glm::mat4(1.0f) , glm::radians(leftAngle), glm::vec3(0,1,0));
    midMatrix = glm::rotate(midMatrix , glm::radians(upAngle), glm::vec3(-1,0,0));
    return midMatrix * direction ;
}
glm::vec4 CAMERA::getRight()
{
    glm::vec4 midvec = getDirection();
    return glm::vec4( glm::cross(glm::vec3(midvec.x , midvec.y , midvec.z) , glm::vec3(0,1,0) ) , 0 );
}
glm::vec3 CAMERA::getPosition()
{
    return glm::vec3( position.x, position.y, position.z );
}



#endif