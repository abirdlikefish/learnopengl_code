#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class VAO
{
public:
    unsigned int ID;
    unsigned int vboID;
    unsigned int veoID;
    VAO(unsigned int  verticesNum , float *vertices , unsigned int  indicesNum , unsigned int *indices);
    ~VAO();
    void use();

};

VAO::VAO(unsigned int  verticesNum , float *vertices , unsigned int  indicesNum , unsigned int *indices)
{
    glGenVertexArrays(1 , &ID );
    glBindVertexArray(ID);

    // unsigned int vbo ;
    glGenBuffers(1, &vboID );
    glBindBuffer(GL_ARRAY_BUFFER , vboID);
    glBufferData(GL_ARRAY_BUFFER, verticesNum * sizeof(float), vertices, GL_STATIC_DRAW );

    // unsigned int veo ;
    glGenBuffers(1, &veoID );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , veoID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , indicesNum * sizeof(unsigned int ), indices, GL_STATIC_DRAW );

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * 8 ,(void *)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float) * 8 ,(void *)(3 * sizeof(float)));
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(float) * 8 ,(void *)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

VAO::~VAO()
{
    glDeleteBuffers(1 , &ID);
    glDeleteBuffers(1 , &vboID);
    glDeleteBuffers(1 , &veoID);
    std::cout << "VAO deleted" << std::endl;
}

void VAO::use()
{
    glBindVertexArray(ID);
}


#endif