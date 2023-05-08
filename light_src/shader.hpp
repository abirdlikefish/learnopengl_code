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

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);
    
    void setUniformui(const char *name, unsigned int data);
    void setUniformi(const char *name, int data);
    void setUniformf(const char *name, float data);
    void setUniformMat(const char *name, glm::mat4 data);
    
    void setUniformVec(const char *name, glm::vec3 data);
public:
    SHADER(const char *vertexShaderPath , const char *fragmentShaderPath);
    ~SHADER();
    void use();
    void setTexture(unsigned int textureNumber);
    
    
    void setModel(float angle , glm::vec3 rotateAxis , glm::vec3 scale , glm::vec3 position);
    void setView(glm::vec3 eyePosition , glm::vec3 viewDirection);
    void setProj(float fov , float aspectRatio , float zNear, float zFar);

    void setPointLightNumber(int number);
    void setPointLightPosition(glm::vec3 lightPosition , int index);
    void setPointLightStrength(glm::vec3 lightStrength , int index);
    void setAmbientFactor_pointLight(glm::vec3 ambientFactor , int index);
    void setDiffuseFactor_pointLight(glm::vec3 diffuseFactor , int index);
    void setSpecularFactor_pointLight(glm::vec3 specularFactor , int index);

    void setDirectionalLightNumber(int number);
    void setDirectionalLightDirection(glm::vec3 lightDirection , int index);
    void setDirectionalLightStrength(glm::vec3 lightStrength , int index);
    void setAmbientFactor_directionalLight(glm::vec3 ambientFactor , int index);
    void setDiffuseFactor_directionalLight(glm::vec3 diffuseFactor , int index);
    void setSpecularFactor_directionalLight(glm::vec3 specularFactor , int index);

    void setSpotLightNumber(int number);
    void setSpotLightDirection(glm::vec3 lightDirection , int index);
    void setSpotLightPosition(glm::vec3 lightPosition , int index);
    void setSpotLightStrength(glm::vec3 lightStrength , int index);
    void setAmbientFactor_spotLight(glm::vec3 ambientFactor , int index);
    void setDiffuseFactor_spotLight(glm::vec3 diffuseFactor , int index);
    void setSpecularFactor_spotLight(glm::vec3 specularFactor , int index);
    void setCutoff_cos(float angle_cos , int index);
    void setOuterCutoff_cos(float angle_cos , int index);

};


// ================================================
// pointLight
void SHADER::setPointLightNumber(int number)
{
    setUniformi("pointLightNumber_v",number);
}
void SHADER::setPointLightPosition(glm::vec3 lightPosition , int index)
{
    std::string name = "pointLightPosition_world[" + std::to_string(index) + "]";
    setUniformVec( name.c_str() , lightPosition);
}
void SHADER::setPointLightStrength(glm::vec3 lightStrength , int index)
{
    std::string name = "pointLight[" + std::to_string(index) + "].strength";
    setUniformVec( name.c_str() , lightStrength);
}
void SHADER::setAmbientFactor_pointLight(glm::vec3 ambientFactor , int index)
{
    std::string name = "pointLight[" + std::to_string(index) + "].ambient";
    setUniformVec( name.c_str() , ambientFactor);
}
void SHADER::setDiffuseFactor_pointLight(glm::vec3 diffuseFactor , int index)
{
    std::string name = "pointLight[" + std::to_string(index) + "].diffuse";
    setUniformVec( name.c_str() , diffuseFactor);
}
void SHADER::setSpecularFactor_pointLight(glm::vec3 specularFactor , int index)
{
    std::string name = "pointLight[" + std::to_string(index) + "].specular";
    setUniformVec( name.c_str() , specularFactor);
}


// ================================================
// directionalLight
void SHADER::setDirectionalLightNumber(int number)
{
    setUniformi("directionalLightNumber_v",number);
    // std::cout << "setDirectionalLight" << std::endl;
}
void SHADER::setDirectionalLightDirection(glm::vec3 lightDirection , int index)
{
    std::string name = "directionalLightDirection_world[" + std::to_string(index) + "]";
    setUniformVec( name.c_str() , lightDirection );
}
void SHADER::setDirectionalLightStrength(glm::vec3 lightStrength , int index)
{
    std::string name = "directionalLight[" + std::to_string(index) + "].strength";
    setUniformVec( name.c_str() , lightStrength);
}
void SHADER::setAmbientFactor_directionalLight(glm::vec3 ambientFactor , int index)
{
    std::string name = "directionalLight[" + std::to_string(index) + "].ambient";
    setUniformVec( name.c_str() , ambientFactor);
}
void SHADER::setDiffuseFactor_directionalLight(glm::vec3 diffuseFactor , int index)
{
    std::string name = "directionalLight[" + std::to_string(index) + "].diffuse";
    setUniformVec( name.c_str() , diffuseFactor);
}
void SHADER::setSpecularFactor_directionalLight(glm::vec3 specularFactor , int index)
{
    std::string name = "directionalLight[" + std::to_string(index) + "].specular";
    setUniformVec( name.c_str() , specularFactor);
}


// ================================================
// spotLight
void SHADER::setSpotLightNumber(int number)
{
    setUniformi("spotLightNumber_v",number);
}
void SHADER::setSpotLightPosition(glm::vec3 lightPosition , int index)
{
    std::string name = "spotLightPosition_world[" + std::to_string(index) + "]";
    setUniformVec( name.c_str() , lightPosition);
}
void SHADER::setSpotLightDirection(glm::vec3 lightDirection , int index)
{
    std::string name = "spotLightDirection_world[" + std::to_string(index) + "]";
    setUniformVec( name.c_str() , lightDirection);
}
void SHADER::setSpotLightStrength(glm::vec3 lightStrength , int index)
{
    std::string name = "spotLight[" + std::to_string(index) + "].strength";
    setUniformVec( name.c_str() , lightStrength);
}
void SHADER::setAmbientFactor_spotLight(glm::vec3 ambientFactor , int index)
{
    std::string name = "spotLight[" + std::to_string(index) + "].ambient";
    setUniformVec( name.c_str() , ambientFactor);
}
void SHADER::setDiffuseFactor_spotLight(glm::vec3 diffuseFactor , int index)
{
    std::string name = "spotLight[" + std::to_string(index) + "].diffuse";
    setUniformVec( name.c_str() , diffuseFactor);
}
void SHADER::setSpecularFactor_spotLight(glm::vec3 specularFactor , int index)
{
    std::string name = "spotLight[" + std::to_string(index) + "].specular";
    setUniformVec( name.c_str() , specularFactor);
}
void SHADER::setCutoff_cos(float angle_cos , int index)
{
    std::string name = "spotLight[" + std::to_string(index) + "].innerCos";
    setUniformf( name.c_str() , angle_cos);
}
void SHADER::setOuterCutoff_cos(float angle_cos , int index)
{
    std::string name = "spotLight[" + std::to_string(index) + "].outerCos";
    setUniformf( name.c_str() , angle_cos);
}



// =============================================
// mvp
void SHADER::setModel(float angle , glm::vec3 rotateAxis , glm::vec3 scale , glm::vec3 position)
{
    modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotateAxis );
    modelMatrix = glm::scale(glm::mat4(1.0f) , scale ) * modelMatrix;
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

// =================================================================
// texture
void SHADER::setTexture(unsigned int textureNumber)
{
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


// ====================================================
// uniform
void SHADER::setUniformui(const char *name, unsigned int data)
{
    glUseProgram(ID);
    int uniformID = glGetUniformLocation(ID , name);
    if(uniformID == -1 )
    {
        std::cerr << "failed to get uniform " << name << " location" << std::endl;
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
        std::cerr << "failed to get uniform " << name << " location" << std::endl;
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
        std::cerr << "failed to get uniform " << name << " location" << std::endl;
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
        std::cerr << "failed to get uniform " << name << " location" << std::endl;
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
        std::cerr << "failed to get uniform " << name << " location" << std::endl;
        exit(-1);
    }

    // glUniformMatrix4fv(uniformID , 1 , GL_FALSE , glm::value_ptr(data) );
    glUniform3f(uniformID ,data.x , data.y , data.z );
}

// =================================================
// initialization
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
    setUniformMat("m" , modelMatrix);
    setUniformMat("v" , viewMatrix);
    setUniformMat("p" , projMatrix);
}

#endif

