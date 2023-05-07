#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <windows.h>
#include <cmath>
#include "shader.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "camera.hpp"
#include "pointLight.hpp"

void framebuffer_size_callback(GLFWwindow *window , int  windowWidth , int  windowHeight );

void mouse_callback(GLFWwindow* window, double mousex, double mousey);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

struct LASTFRAME
{
    float mousex;
    float mousey;
    float time = 0;
};
LASTFRAME lastFrame;

CAMERA *camera;


int main()
{

// =================================================================
// initialization

    glfwInit();     //初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式


    int  windowWidth = 800;
    int  windowHeight = 600;
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight , "LearnOpengl" , NULL , NULL);

    if(window == NULL )
    {
        std::cerr << "ERROR: Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,windowWidth,windowHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window, scroll_callback);



// ===============================================
// camera
    CAMERA camera(glm::vec3(0,0,0 ), glm::vec3( 0 , 0, -1 ) , (float)windowWidth/(float)windowHeight);
    ::camera = &camera;

// ===============================================================
/*
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

*/
    unsigned int  verticesNum = 8 * 4 * 6 ;
    float vertices[] = {
        //前
        -0.5,0.5,0.5,     0,0,1,      0,0.5,
        0.5,0.5,0.5,      0,0,1,      0.5,0.5,
        -0.5,-0.5,0.5,    0,0,1,      0,0,
        0.5,-0.5,0.5,     0,0,1,      0.5,0,
        //后
        0.5,0.5,-0.5,      0,0,-1,      1,1,
        -0.5,0.5,-0.5,     0,0,-1,      0,1,
        0.5,-0.5,-0.5,     0,0,-1,      1,0,
        -0.5,-0.5,-0.5,    0,0,-1,      0,0,
        //上
        -0.5,0.5,-0.5,     0,1,0,      0,1,
        0.5,0.5,-0.5,      0,1,0,      1,1,
        -0.5,0.5,0.5,    0,1,0,      0,0,
        0.5,0.5,0.5,     0,1,0,      1,0,
        //下
        0.5,-0.5,-0.5,      0,-1,0,      1,1,
        -0.5,-0.5,-0.5,     0,-1,0,      0,1,
        0.5,-0.5,0.5,     0,-1,0,      1,0,
        -0.5,-0.5,0.5,    0,-1,0,      0,0,
        //左
        -0.5,0.5,-0.5,     -1,0,0,      0,1,
        -0.5,0.5,0.5,      -1,0,0,      1,1,
        -0.5,-0.5,-0.5,    -1,0,0,      0,0,
        -0.5,-0.5,0.5,     -1,0,0,      1,0,
        //右
        0.5,0.5,0.5,      1,0,0,      1,1,
        0.5,0.5,-0.5,     1,0,0,      0,1,
        0.5,-0.5,0.5,     1,0,0,      1,0,
        0.5,-0.5,-0.5,    1,0,0,      0,0


    };
    float vertices_light[] = {
        //前
        -0.5,0.5,0.5,     0,0,-1,      0,0.5,
        0.5,0.5,0.5,      0,0,-1,      0.5,0.5,
        -0.5,-0.5,0.5,    0,0,-1,      0,0,
        0.5,-0.5,0.5,     0,0,-1,      0.5,0,
        //后
        0.5,0.5,-0.5,      0,0,1,      1,1,
        -0.5,0.5,-0.5,     0,0,1,      0,1,
        0.5,-0.5,-0.5,     0,0,1,      1,0,
        -0.5,-0.5,-0.5,    0,0,1,      0,0,
        //上
        -0.5,0.5,-0.5,     0,-1,0,      0,1,
        0.5,0.5,-0.5,      0,-1,0,      1,1,
        -0.5,0.5,0.5,    0,-1,0,      0,0,
        0.5,0.5,0.5,     0,-1,0,      1,0,
        //下
        0.5,-0.5,-0.5,      0,1,0,      1,1,
        -0.5,-0.5,-0.5,     0,1,0,      0,1,
        0.5,-0.5,0.5,     0,1,0,      1,0,
        -0.5,-0.5,0.5,    0,1,0,      0,0,
        //左
        -0.5,0.5,-0.5,     1,0,0,      0,1,
        -0.5,0.5,0.5,      1,0,0,      1,1,
        -0.5,-0.5,-0.5,    1,0,0,      0,0,
        -0.5,-0.5,0.5,     1,0,0,      1,0,
        //右
        0.5,0.5,0.5,      -1,0,0,      1,1,
        0.5,0.5,-0.5,     -1,0,0,      0,1,
        0.5,-0.5,0.5,     -1,0,0,      1,0,
        0.5,-0.5,-0.5,    -1,0,0,      0,0


    };
    // float vertices[] = {
    //     -0.5,0.5,0,     0,0,0,      -0.5,0.5,
    //     0.5,0.5,0,      0,0,0,      0.5,0.5,
    //     -0.5,-0.5,0,    0,0,0,      -0.5,-0.5,
    //     0.5,-0.5,0,     0,0,0,      0.5,-0.5
    // };
    unsigned int  indicesNum = 3 * 2 * 6;
    unsigned int indices[] = {
        0,2,3,
        0,3,1,

        4,6,7,
        4,7,5,
        
        8,10,11,
        8,11,9,
        
        12,14,15,
        12,15,13,
        
        16,18,19,
        16,19,17,
        
        20,22,23,
        20,23,21

    };


// =================================================================
// set VAO / VBO / EBO

    VAO vao(verticesNum , vertices , indicesNum , indices);
    VAO vao_pointLight(verticesNum , vertices_light , indicesNum , indices);

/*
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
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE, 8 * sizeof(float) , (void*)0 );
    glEnableVertexAttribArray(0);

    //vertex color
    glVertexAttribPointer(1,3,GL_FLOAT , GL_FALSE, 8 * sizeof(float) , (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(1);

    //vertex texture
    glVertexAttribPointer(2,2,GL_FLOAT , GL_FALSE, 8 * sizeof(float) , (void*)(6*sizeof(float)) );
    glEnableVertexAttribArray(2);


//解绑VAO
    glBindVertexArray(0);

*/


// ================================================================= 
// shader
    const char *vertexShaderPath = "./src/vertexShader.shader";
    const char *fragmentShaderPath = "./src/fragmentShader.shader";
    SHADER shader(vertexShaderPath , fragmentShaderPath);

// =================================================================
// texture
    // const char *texturePath0 = "./model/toon2.png";
    // const char *texturePath0 = "./model/box.png";
    const char *diffuseTexturePath = "./model/box_diffuse.jpg";
    const char *specularTexturePath = "./model/box_specular.jpg";
    // const char *texturePath0 = "./model/wall.jpg";
    // const char *texturePath1 = "./model/huaji.jpg";
    // TEXTURE texture(texturePath0 , texturePath1);
    TEXTURE texture(diffuseTexturePath,specularTexturePath);

// =================================================================
// texture_white
    const char *texturePath = "./model/white.jpg";
    TEXTURE texture_white(texturePath);

// =================================================================
// light
    glm::vec3 pointLightPosition[4] = 
    {
        glm::vec3(0 , 2 , -2),
        glm::vec3(2 , 2 , -2),
        glm::vec3(4 , -1 , -2),
        glm::vec3(0 , 2 , 2)
    };
    POINT_LIGHT pointLight0(pointLightPosition[0]);
    POINT_LIGHT pointLight1(pointLightPosition[1]);
    POINT_LIGHT pointLight2(pointLightPosition[2]);
    POINT_LIGHT pointLight3(pointLightPosition[3]);


//============================================================================
//渲染循环
    glEnable(GL_DEPTH_TEST);
    // float lastFrameTime = 0 ;
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

// draw light

        vao_pointLight.use();
        texture_white.use(&shader);
        camera.use(&shader);
        shader.setProj(camera.fov , windowWidth / windowHeight , camera.zNear, camera.zFar);
        shader.setView(camera.getPosition() , camera.getDirection() );
        //0
        pointLight0.use(&shader , 0);
        shader.setModel(0,glm::vec3(0,1,0),glm::vec3(0.05,0.05,0.05),pointLightPosition[0] );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);
        //1
        pointLight1.use(&shader , 1);
        shader.setModel(0,glm::vec3(0,1,0),glm::vec3(0.05,0.05,0.05),pointLightPosition[1] );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);
        //2
        pointLight2.use(&shader , 2);
        shader.setModel(0,glm::vec3(0,1,0),glm::vec3(0.05,0.05,0.05),pointLightPosition[2] );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);
        //3
        pointLight3.use(&shader , 3);
        shader.setModel(0,glm::vec3(0,1,0),glm::vec3(0.05,0.05,0.05),pointLightPosition[3] );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);



// draw box
        vao.use();
        pointLight0.use(&shader,0);
        pointLight1.use(&shader,1);
        pointLight2.use(&shader,2);
        pointLight3.use(&shader,3);
        texture.use(&shader);
        camera.use(&shader);

        shader.setModel(0,glm::vec3(0,1,0),glm::vec3(1,1,1),glm::vec3(0,0,0) );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);

        shader.setModel(0,glm::vec3(0,1,0),glm::vec3(0.5 , 0.5 , 0.5),glm::vec3(-2,0,0) );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);
        
        shader.setModel(30,glm::vec3(0,1,0),glm::vec3(0.5 , 0.5 , 0.5),glm::vec3(2,0,0) );
        shader.use();
        glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //============================================================================
    // glDeleteVertexArrays(1,&VAO);
    // glDeleteBuffers(1,&VBO);

    glfwTerminate();
    return 0;
}


//============================================================================
// function

void framebuffer_size_callback(GLFWwindow *window ,int  windowWidth , int  windowHeight )
{
    glViewport(0,0,windowWidth , windowHeight);
}

void mouse_callback(GLFWwindow* window, double mousex, double mousey)
{
    float offsetx = mousex - lastFrame.mousex;
    float offsety = mousey - lastFrame.mousey;
    lastFrame.mousex = mousex;
    lastFrame.mousey = mousey;
    float sensitivity = 0.05;
    camera -> rotateUp(offsety * sensitivity);
    camera -> rotateLeft(-1 * offsetx * sensitivity);

}

void processInput(GLFWwindow *window)
{
    // float speed = 0.0001;
    float time = glfwGetTime();
    float speed = time - lastFrame.time ;
    lastFrame.time = time;

    if(glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window , true);
    }
    else
    {
        time = fmod(time , 1);
        // glClearColor(time,time, 1-time, 1);
        glClearColor(0,0, 0 , 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    if(glfwGetKey(window ,GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        speed *= 5;
    }
    if(glfwGetKey(window , GLFW_KEY_W) == GLFW_PRESS )
    {
        camera -> moveForward(speed);
    }
    if(glfwGetKey(window , GLFW_KEY_S) == GLFW_PRESS )
    {
        camera -> moveForward(-speed);
    }
    if(glfwGetKey(window , GLFW_KEY_D) == GLFW_PRESS )
    {
        camera -> moveRight(speed);
    }
    if(glfwGetKey(window , GLFW_KEY_A) == GLFW_PRESS )
    {
        camera -> moveRight(-speed);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera -> fov -= yoffset;
    if(camera -> fov < 1 )
        camera -> fov = 1;
    if(camera -> fov > 45)
        camera -> fov = 45;
}

