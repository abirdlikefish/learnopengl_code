#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>

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



// =================================================================
// set vertex and indices

/*
//input three vertices
    float vertices[9];
    std::cout << "input 3 vertices " << std::endl;
    for(int i = 0 ; i < 3 ; i++)
    {
        std::cout << std::endl << "input vertex " << i << ".x = ";
        std::cin >> vertices[i * 3 + 0 ] ;
         
        std::cout << std::endl << "input vertex " << i << ".y = ";
        std::cin >> vertices[i * 3 + 1 ] ;
         
        std::cout << std::endl << "input vertex " << i << ".z = ";
        std::cin >> vertices[i * 3 + 2 ] ;
         
    }
*/

/*
//set three vertices
    float vertices[] = {
        -1,1,0,
        -1,-1,0,
        1,-1,0,
        -0.5,1,0,
        -0.5,-0.5,0,
        1,-0.5,0,
    };
*/
// set 25 vertices
    float vertices[] = {
            -1, 1, 0,
            -0.5, 1, 0,
            0, 1, 0,
            0.5, 1, 0,
            1, 1, 0,
            -1, 0.5, 0,
            -0.5, 0.5, 0,
            0, 0.5, 0,
            0.5, 0.5, 0,
            1, 0.5, 0,
            -1, 0, 0,
            -0.5, 0, 0,
            0, 0, 0,
            0.5, 0, 0,
            1, 0, 0,
            -1, -0.5, 0,
            -0.5, -0.5, 0,
            0, -0.5, 0,
            0.5, -0.5, 0,
            1, -0.5, 0,
            -1, -1, 0,
            -0.5, -1, 0,
            0, -1, 0,
            0.5, -1, 0,
            1, -1, 0
        };


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
    glVertexAttribPointer(0,3,GL_FLOAT , GL_FALSE, 3 * sizeof(float) , (void*)0 );
    glEnableVertexAttribArray(0);

//解绑VAO
    glBindVertexArray(0);




// =================================================================
// shader

//vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char *vertexShader_sourceCode = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    glShaderSource(vertexShader , 1 , &vertexShader_sourceCode , NULL);
    glCompileShader(vertexShader);
    
    int vertexShaderCompileSuccess ;
    glGetShaderiv(vertexShader , GL_COMPILE_STATUS , &vertexShaderCompileSuccess);
    if(vertexShaderCompileSuccess == 0)
    {
        std::cout << "vertex Shader compilation failed " << std::endl;
        glfwTerminate();
        return -1;
    }


//fragment shader orange
    unsigned int fragmentShader_orange = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShader_orange_sourceCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "} \n";

    glShaderSource(fragmentShader_orange , 1 , &fragmentShader_orange_sourceCode , NULL);
    glCompileShader(fragmentShader_orange);

    int fragmentShader_orangeCompileSuccess ;
    glGetShaderiv(fragmentShader_orange , GL_COMPILE_STATUS , &fragmentShader_orangeCompileSuccess);
    if(fragmentShader_orangeCompileSuccess == 0)
    {
        std::cout << "fragment Shader compilation failed " << std::endl;
        glfwTerminate();
        return -1;
    }

    

//fragment shader red
    unsigned int fragmentShader_red = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShader_red_sourceCode = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(0.7f, 0.2f, 0.2f, 0.5f);\n"
    "} \n";

    glShaderSource(fragmentShader_red , 1 , &fragmentShader_red_sourceCode , NULL);
    glCompileShader(fragmentShader_red);

    int fragmentShader_redCompileSuccess ;
    glGetShaderiv(fragmentShader_red , GL_COMPILE_STATUS , &fragmentShader_redCompileSuccess);
    if(fragmentShader_redCompileSuccess == 0)
    {
        std::cout << "fragment Shader compilation failed " << std::endl;
        glfwTerminate();
        return -1;
    }


//shader program orange
    unsigned int shaderProgram_orange = glCreateProgram();

    glAttachShader( shaderProgram_orange , vertexShader );
    glAttachShader( shaderProgram_orange , fragmentShader_orange );

    glLinkProgram(shaderProgram_orange);

//shader program red
    unsigned int shaderProgram_red = glCreateProgram();

    glAttachShader( shaderProgram_red , vertexShader );
    glAttachShader( shaderProgram_red , fragmentShader_red );

    glLinkProgram(shaderProgram_red );


// delete used shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader_orange);
    glDeleteShader(fragmentShader_red);



//============================================================================
//渲染循环
    float time = 0;
    float move = 0.00001;
    while(!glfwWindowShouldClose(window))
    {
        time += move;
        if(time >= 1 || time <= 0 )
            move *= -1;;
        processInput(window , time);


// draw
        glBindVertexArray(VAO);
        glUseProgram(shaderProgram_orange);

        glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);

        // glUseProgram(shaderProgram_orange);
        // glDrawArrays(GL_TRIANGLE_FAN,0,25);

        // glUseProgram(shaderProgram_red);
        // glDrawArrays(GL_TRIANGLES,3,3);



        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    //============================================================================
    glDeleteProgram(shaderProgram_orange);
    glDeleteProgram(shaderProgram_red);
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


