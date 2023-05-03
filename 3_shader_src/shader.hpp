#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class SHADER 
{
private:
    unsigned int ID;

public:
    SHADER(const char *vertexShaderPath , const char *fragmentShaderPath);
    ~SHADER();
    void inputVec3(float input);
    void use();


};

void SHADER::inputVec3(float input)
{
    int uniformID = glGetUniformLocation(ID , "colorOffset");
    if(uniformID == -1)
    {
        std::cerr << "uniformID lost" << std::endl;
    }
    glUniform1f(uniformID , input);
}
SHADER::SHADER(const char *vertexShaderPath , const char *fragmentShaderPath)
{
    // const char *vertexShaderCode;
    // const char *fragmentShaderCode;
    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    // 保证ifstream对象可以抛出异常：
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        std::cout << "a" << std::endl;
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        std::cout << "a" << std::endl;

        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        std::cout << "a" << std::endl;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        std::cout << "a" << std::endl;
        vertexShaderFile.close();
        fragmentShaderFile.close();
        std::cout << "a" << std::endl;

        vertexShaderCode = vertexShaderStream.str();
        fragmentShaderCode = fragmentShaderStream.str();
        std::cout << "a" << std::endl;
        
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
    std::cerr << "b\n";
}

// inline void SHADER::use()
void SHADER::use()
{
    glUseProgram(ID);
}

#endif

