#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n "
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


void framebuffer_size_callback(GLFWwindow * window, int widht, int height);


int main()
{
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FOWARD_COMPAT, GL_TRUE);

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt (3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt (3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt (3)) * 2 / 3, 0.0f
    };

    GLFWwindow* window;
   
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
     if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL();

    glViewport(0, 0, 640, 480);


    //All this portion of code will be updated and even goes to another file, after (maybe).
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //end of /\ this part of maybe "go to another file" code
    /*--------------------------------------------------------------------*/

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    
    glfwSwapBuffers(window); // - Todos os problemas de código, com viewport, 
   // com glClearColor e glClear eram causados pelo fato de "SwapBuffers" 
   // não estar no looping de renderização.


  //  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*Activate Shader Program*/
        glUseProgram(shaderProgram);

        //Pay attention to this part - !!!
        glBindVertexArray(VAO);

        /* NO necessray explanation here*/
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //Block added in 19/02/2025 - unable and destroy if necessary!
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //Test glfwDestroyWindow - added in feb 19th / 2025
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int widht, int height)
{
    glViewport(0, 0, widht, height);
}