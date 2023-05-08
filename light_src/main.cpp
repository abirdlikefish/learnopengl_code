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
#include "directionalLight.hpp"
#include "spotLight.hpp"

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


// ================================================================= 
// shader
    const char *vertexShaderPath = "./src/vertexShader.shader";
    const char *fragmentShaderPath = "./src/fragmentShader.shader";
    SHADER shader(vertexShaderPath , fragmentShaderPath);

// =================================================================
// texture
    const char *diffuseTexturePath = "./model/box_diffuse.jpg";
    const char *specularTexturePath = "./model/box_specular.jpg";
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
    POINT_LIGHT pointLight(4);
    for(int i = 0; i < 4; i++)
    {
        pointLight.setPointLight(i , pointLightPosition[i]);
    }

    DIRECTIONAL_LIGHT directionalLight(1);
    directionalLight.setDirectionalLight(0 , glm::vec3(1 , -1 , 0));

    SPOT_LIGHT spotLight(1);

//============================================================================
//渲染循环

    glEnable(GL_DEPTH_TEST);

    pointLight.use(&shader);
    directionalLight.use(&shader);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

// draw light

        vao_pointLight.use();
        texture_white.use(&shader);
        camera.use(&shader);
        shader.setProj(camera.fov , windowWidth / windowHeight , camera.zNear, camera.zFar);
        shader.setView(camera.getPosition() , camera.getDirection() );
        for(int i = 0 ; i < 4 ; i ++)
        {
            shader.setModel(0,glm::vec3(0,1,0),glm::vec3(0.05,0.05,0.05),pointLightPosition[i] );
            shader.use();
            glDrawElements(GL_TRIANGLES , indicesNum , GL_UNSIGNED_INT , 0);

        }


// draw box
        vao.use();
        texture.use(&shader);
        camera.use(&shader);
        
        spotLight.setSpotLight(0 , camera.getPosition() , camera.getDirection() );
        spotLight.use(&shader);

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
    float time = glfwGetTime();
    float speed = (time - lastFrame.time) * 5;
    lastFrame.time = time;

    if(glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window , true);
    }
    else
    {
        time = fmod(time , 1);
        glClearColor(time,time, 1-time, 1);
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

