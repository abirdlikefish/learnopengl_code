#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include <cmath>
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow *window , int windowWidth , int windowHeight );

void processInput(GLFWwindow *window , float time);


int main()
{

  
// =================================================================
// initialization

    glfwInit();     //初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式


    int windowWidth = 800;
    int windowHeight = 600;
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight , "LearnOpengl" , NULL , NULL);

    if(window == NULL )
    {
        std::cout << "ERROR: Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,windowWidth,windowHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



// ===============================================================
    float vertices[] = {
            -1, 1, 0,
            -1, 1, 0,
            -0.5, 1, 0,
            -0.5, 1, 0,
            0, 1, 0,
            0, 1, 0,
            0.5, 1, 0,
            0.5, 1, 0,
            1, 1, 0,
            1, 1, 0,
            -1, 0.5, 0,
            -1, 0.5, 0,
            -0.5, 0.5, 0,
            -0.5, 0.5, 0,
            0, 0.5, 0,
            0, 0.5, 0,
            0.5, 0.5, 0,
            0.5, 0.5, 0,
            1, 0.5, 0,
            1, 0.5, 0,
            -1, 0, 0,
            -1, 0, 0,
            -0.5, 0, 0,
            -0.5, 0, 0,
            0, 0, 0,
            0, 0, 0,
            0.5, 0, 0,
            0.5, 0, 0,
            1, 0, 0,
            1, 0, 0,
            -1, -0.5, 0,
            -1, -0.5, 0,
            -0.5, -0.5, 0,
            -0.5, -0.5, 0,
            0, -0.5, 0,
            0, -0.5, 0,
            0.5, -0.5, 0,
            0.5, -0.5, 0,
            1, -0.5, 0,
            1, -0.5, 0,
            -1, -1, 0,
            -1, -1, 0,
            -0.5, -1, 0,
            -0.5, -1, 0,
            0, -1, 0,
            0, -1, 0,
            0.5, -1, 0,
            0.5, -1, 0,
            1, -1, 0,
            1, -1, 0
        };

/*
    float vertices[] = {
        0,1,0,
        0,1,0,
        0,0,0,
        0,0,0,
        1,0,0,
        1,0,0
    };

*/
    unsigned int indices[] = {
        0,5,6,
        2,6,7
    };



// =================================================================
// set VAO / VBO / EBO

//设置VAO
    unsigned int VAO ;
    glGenVertexArrays(1 , &VAO);
    glBindVertexArray(VAO);

//设置VBO
    unsigned int VBO ;
    glGenBuffers(1 , &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

//设置EBO
    unsigned int EBO ;
    glGenBuffers(1 , &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

//设置顶点属性
    //vertex position
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE, 6 * sizeof(float) , (void*)0 );
    glEnableVertexAttribArray(0);

    //vertex color
    glVertexAttribPointer(1,3,GL_FLOAT , GL_FALSE, 6 * sizeof(float) , (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);

//解绑VAO
    glBindVertexArray(0);



// ================================================================= 
// shader
    const char *vertexShaderPath = "./src/vertexShader.shader";
    const char *fragmentShaderPath = "./src/fragmentShader.shader";
    SHADER shader(vertexShaderPath , fragmentShaderPath);

//============================================================================
//渲染循环
    // float time = 0;
    while(!glfwWindowShouldClose(window))
    {
        // time += move;
        float time = glfwGetTime();
        // std::cout<<time<<std::endl;
        time = fmod(time , 1);
        processInput(window , time);

        shader.use();
        shader.inputVec3(time);

// draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);
        // glDrawArrays(GL_TRIANGLES,0,3);

        // glUseProgram(shaderProgram_orange);
        // glDrawArrays(GL_TRIANGLE_FAN,0,25);

        // glUseProgram(shaderProgram_red);
        // glDrawArrays(GL_TRIANGLES,3,3);



        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //============================================================================
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);

    glfwTerminate();
    return 0;
}


//============================================================================
// function

void framebuffer_size_callback(GLFWwindow *window , int windowWidth , int windowHeight )
{
    glViewport(0,0,windowWidth , windowHeight);
}

void processInput(GLFWwindow *window , float time)
{
    if(glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window , true);
    }
    else
    {
        glClearColor(time,time, 1-time, 1);
        // glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
        glClear(GL_COLOR_BUFFER_BIT);

    }
}


