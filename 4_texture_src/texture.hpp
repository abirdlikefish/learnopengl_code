#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class TEXTURE 
{
public:
    unsigned int ID[20];
    int textureNumber;
    TEXTURE(const char* texturePath , unsigned int shaderID);
    TEXTURE(const char* texturePath0 , const char* texturePath1 , unsigned int shaderID);
    TEXTURE(const char* texturePath0 , const char* texturePath1 , const char* texturePath2 , unsigned int shaderID);
    void use(unsigned int shaderID);
private:
    unsigned int initialization(const char* texturePath);
};

void TEXTURE::use(unsigned int shaderID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID[0]);

    if(textureNumber < 2)
        return;

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ID[1]);

    if(textureNumber < 3)
        return;

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, ID[2]);

}

TEXTURE::TEXTURE(const char* texturePath , unsigned int shaderID)
{
    textureNumber = 1;
    glUseProgram(shaderID);
    int uniformID = glGetUniformLocation(shaderID , "textureNumber");
    if(uniformID == -1)
    {
        std::cerr << "failed to get uniform " << std::endl;
    }
    glUniform1i(uniformID , textureNumber);

    uniformID = glGetUniformLocation(shaderID , "texture0");
    if(uniformID == -1)
    {
        std::cerr << "failed to get texture0 " << std::endl;
    }
    glUniform1i(uniformID , 0);

    ID[0] = initialization(texturePath);
}

TEXTURE::TEXTURE(const char* texturePath0 , const char* texturePath1 , unsigned int shaderID)
{
    textureNumber = 2;
    glUseProgram(shaderID);
    int uniformID = glGetUniformLocation(shaderID , "textureNumber");
    if(uniformID == -1)
    {
        std::cerr << "failed to get uniform " << std::endl;
    }
    glUniform1i(uniformID , textureNumber);

    uniformID = glGetUniformLocation(shaderID , "texture0");
    if(uniformID == -1)
    {
        std::cerr << "failed to get texture0 " << std::endl;
    }
    glUniform1i(uniformID , 0);
    uniformID = glGetUniformLocation(shaderID , "texture1");
    if(uniformID == -1)
    {
        std::cerr << "failed to get texture1 " << std::endl;
    }
    glUniform1i(uniformID , 1);

    ID[0] = initialization(texturePath0);
    ID[1] = initialization(texturePath1);
    
}
TEXTURE::TEXTURE(const char* texturePath0 , const char* texturePath1 , const char* texturePath2 , unsigned int shaderID)
{
    textureNumber = 3;
    glUseProgram(shaderID);
    int uniformID = glGetUniformLocation(shaderID , "textureNumber");
    if(uniformID == -1)
    {
        std::cerr << "failed to get uniform " << std::endl;
    }
    glUniform1i(uniformID , textureNumber);

    uniformID = glGetUniformLocation(shaderID , "texture0");
    if(uniformID == -1)
    {
        std::cerr << "failed to get texture0 " << std::endl;
    }
    glUniform1i(uniformID , 0);
    uniformID = glGetUniformLocation(shaderID , "texture1");
    if(uniformID == -1)
    {
        std::cerr << "failed to get texture1 " << std::endl;
    }
    glUniform1i(uniformID , 1);
    uniformID = glGetUniformLocation(shaderID , "texture2");
    if(uniformID == -1)
    {
        std::cerr << "failed to get texture2 " << std::endl;
    }
    glUniform1i(uniformID , 2);

    ID[0] = initialization(texturePath0);
    ID[1] = initialization(texturePath1);
    ID[2] = initialization(texturePath2);
    
}

unsigned int TEXTURE::initialization(const char* texturePath)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned int ID;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels,0);

    if(data == NULL)
    {
        std::cerr << "texture load failed" << std::endl;
    }

    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);
    glTexImage2D(GL_TEXTURE_2D , 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S,GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);

    // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    return ID;
}

#endif