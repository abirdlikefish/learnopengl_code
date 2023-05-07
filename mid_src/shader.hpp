#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SHADER 
{
private:
    unsigned int ID;
    unsigned int textureNumber;
    glm::vec3 lightPosition[4];
    glm::vec3 lightStrength[4];
    glm::vec3 ambientFactor[4];
    glm::vec3 diffuseFactor[4];
    glm::vec3 specularFactor[4];
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);
public:
    SHADER(const char *vertexShaderPath , const char *fragmentShaderPath);
    ~SHADER();
    void use();
    void setTexture(unsigned int textureNumber);
    void setUniformui(const char *name, unsigned int data);
    void setUniformi(const char *name, int data);
    void setUniformf(const char *name, float data);
    void setUniformMat(const char *name, glm::mat4 data);
    void setUniformVec(const char *name, glm::vec3 data);
    
    void setModel(float angle , glm::vec3 rotateAxis , glm::vec3 scale , glm::vec3 position);
    void setView(glm::vec3 eyePosition , glm::vec3 viewDirection);
    void setProj(float fov , float aspectRatio , float zNear, float zFar);
    void setLightPosition(glm::vec3 lightPosition , int index);
    void setLightStrength(glm::vec3 lightStrength , int index);
    void setAmbientFactor(glm::vec3 ambientFactor , int index);
    void setDiffuseFactor(glm::vec3 diffuseFactor , int index);
    void setSpecularFactor(glm::vec3 specularFactor , int index);

};

void SHADER::setLightPosition(glm::vec3 lightPosition , int index)
{
    this -> lightPosition[index] = lightPosition;
}
void SHADER::setLightStrength(glm::vec3 lightStrength , int index)
{
    this -> lightStrength[index] = lightStrength;
    // std::cout << lightStrength.x << " " << lightStrength.y << " " << lightStrength.z << std::endl;
}
void SHADER::setAmbientFactor(glm::vec3 ambientFactor , int index)
{
    this -> ambientFactor[index] = ambientFactor;
}
void SHADER::setDiffuseFactor(glm::vec3 diffuseFactor , int index)
{
    this -> diffuseFactor[index] = diffuseFactor;
}
void SHADER::setSpecularFactor(glm::vec3 specularFactor , int index)
{
    this -> specularFactor[index] = specularFactor;
}

void SHADER::setModel(float angle , glm::vec3 rotateAxis , glm::vec3 scale , glm::vec3 position)
{
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotateAxis );
    modelMatrix = glm::scale(glm::mat4(1.0f) , scale ) * modelMatrix;
    // modelMatrix = glm::translate(modelMatrix , position );
    modelMatrix = glm::translate(glm::mat4(1.0f) , position ) * modelMatrix;
}
void SHADER::setView(glm::vec3 eyePosition , glm::vec3 viewDirection)
{
    viewMatrix = glm::lookAt(eyePosition , eyePosition + viewDirection , glm::vec3(0,1,0) );
}

void SHADER::setProj(float fov , float aspectRatio , float zNear, float zFar)
{
    projMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}


void SHADER::setTexture(unsigned int textureNumber)
{
    this->textureNumber = textureNumber;
    if(textureNumber <= 1)
    {
        setUniformi("material.diffuseTexture" , 0 );
    }
    else if(textureNumber <= 2 )
    {
        setUniformi("material.diffuseTexture" , 0 );
        setUniformi("material.specularTexture" , 1 );
        setUniformf("material.shininess" , 100 );
    }
    else
    {
        std::cerr << "Invalid texture number" << std::endl;
    }

}

void SHADER::setUniformui(const char *name, unsigned int data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failed to get uniform " << name << "location" << std::endl;
        exit(-1);
    }

    glUniform1ui(uniformID , data );
}

void SHADER::setUniformi(const char *name, int data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failed to get uniform " << name << "location" << std::endl;
        exit(-1);

    }

    glUniform1i(uniformID , data );
}
void SHADER::setUniformf(const char *name, float data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failed to get uniform " << name << "location" << std::endl;
        exit(-1);
    }

    glUniform1f(uniformID , data );
}

void SHADER::setUniformMat(const char *name, glm::mat4 data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failed to get uniform " << name << "location" << std::endl;
        exit(-1);
    }

    glUniformMatrix4fv(uniformID , 1 , GL_FALSE , glm::value_ptr(data) );
}

void SHADER::setUniformVec(const char *name, glm::vec3 data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failed to get uniform " << name << "location" << std::endl;
        exit(-1);
    }

    // glUniformMatrix4fv(uniformID , 1 , GL_FALSE , glm::value_ptr(data) );
    glUniform3f(uniformID ,data.x , data.y , data.z );
}


/*
void SHADER::inputMixParameter(float mixParameter)
{
    int mixParameterID = glGetUniformLocation(ID , "mixParameter");
    if(mixParameterID == -1)
    {
        std::cerr << "failed to get mixParameterID" << std::endl;
    }
    glUniform1f(ID , mixParameter);
}
*/
/*

void SHADER::inputVec3(float input)
{
    int uniformID = glGetUniformLocation(ID , "colorOffset");
    if(uniformID == -1)
    {
        std::cerr << "uniformID lost" << std::endl;
    }
    glUniform1f(uniformID , input);
}
*/

SHADER::SHADER(const char *vertexShaderPath , const char *fragmentShaderPath)
{
    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    // 保证ifstream对象可以抛出异常：
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShaderCode = vertexShaderStream.str();
        fragmentShaderCode = fragmentShaderStream.str();
        
    }
    catch(std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        exit(-1);
    }
    
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderCodePointer = vertexShaderCode.c_str();
    const char *fragmentShaderCodePointer = fragmentShaderCode.c_str();

    glShaderSource(vertexShaderID,1,&vertexShaderCodePointer,NULL);
    glShaderSource(fragmentShaderID,1,&fragmentShaderCodePointer,NULL);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    int success = 0;
    char infoLog[512];

    glGetShaderiv(vertexShaderID , GL_COMPILE_STATUS , &success );
    if(!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        std::cerr << "Could not compile vertex shader \n" << infoLog <<std::endl;
        exit(-1);
    }

    glGetShaderiv(fragmentShaderID , GL_COMPILE_STATUS , &success );
    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cerr << "Could not compile fragment shader\n" << infoLog << std::endl;
        exit(-1);
    }

    ID = glCreateProgram();
    glAttachShader(ID , vertexShaderID);
    glAttachShader(ID , fragmentShaderID);
    glLinkProgram(ID);

    glGetProgramiv(ID , GL_LINK_STATUS , &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "Could not link shader\n" << infoLog <<std::endl;
        exit(-1);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    

}

SHADER::~SHADER()
{
    glDeleteProgram(ID);
    std::cout << "Shader deleted" << std::endl;
}

// inline void SHADER::use()
void SHADER::use()
{
    glUseProgram(ID);
    setUniformVec("lightPosition", lightPosition);
    setUniformVec("lightStrength", lightStrength);
    setUniformVec("light.ambient", ambientFactor);
    setUniformVec("light.diffuse", diffuseFactor);
    setUniformVec("light.specular", specularFactor);

    setUniformMat("m" , modelMatrix);
    setUniformMat("v" , viewMatrix);
    setUniformMat("p" , projMatrix);
}

#endif

