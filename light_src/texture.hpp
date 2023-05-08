#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"

class TEXTURE 
{
public:
    TEXTURE(const char* diffuseTexturePath );
    TEXTURE(const char* diffuseTexturePath , const char* specularTexturePath);
    // TEXTURE(const char* texturePath0 , const char* texturePath1 , const char* texturePath2);
    void use(SHADER *shader);
private:
    int textureNumber;
    unsigned int ID[20];
    unsigned int initialization(const char* texturePath);
};

void TEXTURE::use(SHADER *shader)
{
    
    shader -> setTexture(textureNumber);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID[0]);

    if(textureNumber < 2)
        return;

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ID[1]);

}

TEXTURE::TEXTURE(const char* diffuseTexturePath )
{
    textureNumber = 1;
    ID[0] = initialization(diffuseTexturePath);
}

TEXTURE::TEXTURE(const char* diffuseTexturePath , const char* specularTexturePath)
{
    textureNumber = 2;
    ID[0] = initialization(diffuseTexturePath);
    ID[1] = initialization(specularTexturePath);
    
}
// TEXTURE::TEXTURE(const char* texturePath0 , const char* texturePath1 , const char* texturePath2)
// {
//     textureNumber = 3; 
//     ID[0] = initialization(texturePath0);
//     ID[1] = initialization(texturePath1);
//     ID[2] = initialization(texturePath2);
    
// }

unsigned int  TEXTURE::initialization(const char* texturePath)
{
    //上下颠倒
    stbi_set_flip_vertically_on_load(true);

    int  width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels,0);
    if(data == NULL)
    {
        std::cerr << "texture load failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int ID;
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);
    glTexImage2D(GL_TEXTURE_2D , 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
    return ID;
}

#endif