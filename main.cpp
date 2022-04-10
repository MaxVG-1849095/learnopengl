#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool wireframing = false;
// shader
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // fragnent shader heeft aar 1 output nodig en dit is een vector met grootte 4 voor de kleur
                                   "}\n\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n" // fragnent shader heeft aar 1 output nodig en dit is een vector met grootte 4 voor de kleur
                                   "}\n\0";
// prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int main()
{
    glfwInit();                                    // glfw init
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfw config
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); // width, height, name, NULL,NULL
    if (window == NULL)
    {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600); // locatie linkse onderhoek van het window, grootte van het window (functie die opengl de grootte van het window verteld en waar het is)

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // shaders
    //------------------------
    // vertex shader
    unsigned int vertexShader;                                  // store shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);            // maak shader, (type van de shader)
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // hang shader bron aan shader (staat bovenaan) (shader, aantal strings, bron, NULL)
    glCompileShader(vertexShader);                              // compile de shader

    // check voor shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // fragment shader
    unsigned int fragmentShader[2];
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader[0]);
    // check for shader compile errors
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader[1]);
    // check for shader compile errors
    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Shaders linken

    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram(); // maak program en return de if ervan

    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader[0]);
    
    glLinkProgram(shaderProgram[0]);
    // check for linking errors
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader); // delete na linken
    glDeleteShader(fragmentShader[0]);


    shaderProgram[1] = glCreateProgram(); // maak program en return de if ervan
    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShader[1]);
    
    glLinkProgram(shaderProgram[1]);
    // check for linking errors
    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(fragmentShader[1]);
    // driehoek
    //----------------------------------
    // float vertices[] = {
    //     0.5f, 0.5f, 0.0f,   // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f   // top left
    // };
    float vertices[] = {
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        -0.25f, 0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.25f, 0.5f, 0.0f};
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int EBO; // element buffer object
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO;      // vertex buffer object, voor memory te managen op de gpu voor de vertices te bewaren
    glGenBuffers(1, &VBO); // opengl object met id 1
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // hoe opengl de vertex data moet interpreteren (vertex pos, size(vec3 ->3 vals),type,data normaliseren?, stride, offset met typecast  )
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) // render loop
    {
        // input
        processInput(window); // input handler

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // zet de clearkleur
        glClear(GL_COLOR_BUFFER_BIT);         // clear het scherm naar de kleur
        glUseProgram(shaderProgram[0]);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); //(primitive, startindex, aantal vertices) (voor vertex tekenen)


        glUseProgram(shaderProgram[1]);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,2,3);
        if (wireframing)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //element tekenen

        // pollevents en swapbuffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
// functie voor resize van het window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
// input functie, moet in render loop staan
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // escape = close window
    {
        std::cout << "escape pressed" << std::endl;
        glfwSetWindowShouldClose(window, true); // bool van render loop
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) // p = print message
    {
        std::cout << "P pressed" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) // p = print message
    {
        std::cout << "Wireframing" << std::endl;
        wireframing = !wireframing;
        std::cout << wireframing << std::endl;
    }
}