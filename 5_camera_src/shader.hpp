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
private:
    unsigned int ID;
    unsigned int textureNumber;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);
public:
    SHADER(const char *vertexShaderPath , const char *fragmentShaderPath);
    ~SHADER();
    void use();
    void setTextureNumber(unsigned int textureNumber);
    void setUniformui(const char *name, unsigned int data);
    void setUniformi(const char *name, int data);
    void setUniformf(const char *name, float data);
    void setUniformMat(const char *name, glm::mat4 data);
    void setModel();
    void setView(glm::vec3 eyePosition , glm::vec3 viewDirection);
    void setProj(float fov , float aspectRatio , float zNear, float zFar);

};

void SHADER::setModel()
{
    ;
}
void SHADER::setView(glm::vec3 eyePosition , glm::vec3 viewDirection)
{
    viewMatrix = glm::lookAt(eyePosition , eyePosition + viewDirection , glm::vec3(0,1,0) );
}

void SHADER::setProj(float fov , float aspectRatio , float zNear, float zFar)
{
    projMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}


void SHADER::setTextureNumber(unsigned int textureNumber)
{
    this->textureNumber = textureNumber;
    setUniformi("textureNumber" , textureNumber );

    if(textureNumber <= 1)
    {
        setUniformi("texture0" , 0 );
    }
    else if(textureNumber <= 2 )
    {
        setUniformi("texture1" , 1 );
    }
    else if(textureNumber <= 3 )
    {
        setUniformi("texture2" , 2 );
    }

}

void SHADER::setUniformui(const char *name, unsigned int data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failef to get uniform " << name << "location" << std::endl;
    }

    glUniform1ui(uniformID , data );
}

void SHADER::setUniformi(const char *name, int data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failef to get uniform " << name << "location" << std::endl;
    }

    glUniform1i(uniformID , data );
}
void SHADER::setUniformf(const char *name, float data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failef to get uniform " << name << "location" << std::endl;
    }

    glUniform1f(uniformID , data );
}

void SHADER::setUniformMat(const char *name, glm::mat4 data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failef to get uniform " << name << "location" << std::endl;
    }

    glUniformMatrix4fv(uniformID , 1 , GL_FALSE , glm::value_ptr(data) );
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
    
    glGetShaderiv(vertexShaderID , GL_COMPILE_STATUS , &success );
    if(!success)
        std::cerr << "Could not compile vertex shader" << std::endl;

    glGetShaderiv(fragmentShaderID , GL_COMPILE_STATUS , &success );
    if(!success)
        std::cerr << "Could not compile fragment shader" << std::endl;

    ID = glCreateProgram();
    glAttachShader(ID , vertexShaderID);
    glAttachShader(ID , fragmentShaderID);
    glLinkProgram(ID);

    glGetProgramiv(ID , GL_LINK_STATUS , &success);
    if(!success)
        std::cerr << "Could not link shader" << std::endl;

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
    setUniformMat("mvp" , projMatrix * viewMatrix * modelMatrix);
}

#endif

