#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include "stb_image.h"
#include "shader.h"

bool wireframing = false;
// shaders, Vertexshader zorgt voor het
// Fragment shader zorgt voor de kleur
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   ourColor = aColor;\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(ourColor, 1.0f);\n"
                                   "}\n\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "in vec3 ourColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(ourColor, 1.0f);\n"
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
    Shader ourShader("3.3.Shader.vs", "3.3.Shader.fs"); // you can name your shader files however you like

    // // vertex shader
    // unsigned int vertexShader;                                  // store shader
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);            // maak shader, (type van de shader)
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // hang shader bron aan shader (staat bovenaan) (shader, aantal strings, bron, NULL)
    // glCompileShader(vertexShader);                              // compile de shader

    // // check voor shader compile errors
    // int success;
    // char infoLog[512];
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
    //               << infoLog << std::endl;
    // }

    // // fragment shader
    // unsigned int fragmentShader[2];
    // fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader[0], 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader[0]);
    // // check for shader compile errors
    // glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
    //               << infoLog << std::endl;
    // }

    // fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);
    // glCompileShader(fragmentShader[1]);
    // // check for shader compile errors
    // glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
    //               << infoLog << std::endl;
    // }

    // // Shaders linken

    // unsigned int shaderProgram[2];
    // shaderProgram[0] = glCreateProgram(); // maak program en return de if ervan

    // glAttachShader(shaderProgram[0], vertexShader);
    // glAttachShader(shaderProgram[0], fragmentShader[0]);

    // glLinkProgram(shaderProgram[0]);
    // // check for linking errors
    // glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    // if (!success)
    // {
    //     glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
    //               << infoLog << std::endl;
    // }
    // glDeleteShader(vertexShader); // delete na linken
    // glDeleteShader(fragmentShader[0]);

    // shaderProgram[1] = glCreateProgram(); // maak program en return de if ervan
    // glAttachShader(shaderProgram[1], vertexShader);
    // glAttachShader(shaderProgram[1], fragmentShader[1]);

    // glLinkProgram(shaderProgram[1]);
    // // check for linking errors
    // glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    // if (!success)
    // {
    //     glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
    //               << infoLog << std::endl;
    // }
    // glDeleteShader(fragmentShader[1]);
    // driehoek
    //----------------------------------
    // float vertices[] = {
    //     0.5f, 0.5f, 0.0f,   // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f   // top left
    // };

    //---------------------------------------------
    // vertices
    //---------------------------------------------
    // float vertices[] = {
    //     // positions          // colors           // texture coords
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    // };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    unsigned int indices[] = {
        // voor EBO met drawelement
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VBO;      // vertex buffer object, voor memory te managen op de gpu voor de vertices te bewaren
    glGenBuffers(1, &VBO); // opengl object met id 1
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO; // element buffer object, om via drawelement te kunnen tekenen
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // hoe opengl de vertex data moet interpreteren (vertex pos, size(vec3 ->3 vals),type,data normaliseren?, stride, offset met typecast  )
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // kleur data
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float))); // texture data
    // glEnableVertexAttribArray(2);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //---------------------------------------------
    // Textures
    //---------------------------------------------
    int width, height, nrChannels;

    unsigned int texture;                                         // texture object
    glGenTextures(1, &texture);                                   // aantal textures, int voor id
    glBindTexture(GL_TEXTURE_2D, texture);                        // binding texture to id
                                                                  // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0); // location file, width, height, color channels
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // Texture target (2d). mipmap level, format, width, height, 0, format, datatype, image data
        // Nu hangt de data aan de id
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // flip face
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();

    glUniform1i(glGetUniformLocation(ourShader.ID, "texture"), 0); // manier 1
    ourShader.setInt("texture2", 1);                               // manier 2

    // glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); //maak vector aan
    // glm::mat4 trans = glm::mat4(1.0f); //transformatiematrix (dit is identiteitsmatrix!)
    // trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); //aanmaken transformatiematrix
    // vec = trans * vec; //transformatie uitvoeren op de vector via transformatiematrix
    // std::cout << vec.x << vec.y << vec.z << std::endl;
    float rotation = 0.0f;

    glEnable(GL_DEPTH_TEST); // z-buffer

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    float rotateAngle = 0.0f;
    while (!glfwWindowShouldClose(window)) // render loop
    {
        // input
        processInput(window); // input handler

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);               // zet de clearkleur
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear het scherm naar de kleur
        // glUseProgram(shaderProgram[0]);
        // ourShader.use();u
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3); //(primitive, startindex, aantal vertices) (voor vertex tekenen)

        // glUseProgram(shaderProgram[1]);
        // int colorLocation = glGetUniformLocation(shaderProgram[1], "ourColor"); //haal locatie van uniform op
        // float timeValue = glfwGetTime();
        // float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // glUniform4f(colorLocation, 0.0f,greenValue,0.0f,1.0f); //stuur groen door naar uniform

        // ourShader.use();
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 3, 3);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // rotation += 1.0f;
        // std::cout << rotation << std::endl;
        // glm::mat4 trans = glm::mat4(1.0f);                                         // identiteitsmatrix
        // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 1.0f));               // beweging met 1 op iedere as
        // trans = glm::rotate(trans, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0)); // roteer met 90 graden rond de z-as
        // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));                       // scale met 0.5 op iedere kant

        // render container
        ourShader.use();
        // create transformations
        // glm::mat4 model = glm::mat4(1.0f);
        // // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //plat leggen
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // weg in de z richting (moet binnen -1 1 blijven voor x en y!)

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // perspective (fov, screensize, close, far) close en far zijn standardised

        // passing uniforms to shader
        // int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        rotateAngle += 1.0f;
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if(i % 3 ==0){
                model = glm::rotate(model, glm::radians(angle + rotateAngle), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            else{
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            
            int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glm::mat4 trans2 = glm::mat4(1.0f);                                         // identiteitsmatrix
        // trans2 = glm::translate(trans2, glm::vec3(0.5f, 0.5f, 1.0f));               // beweging met 1 op iedere as
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans2));
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if (wireframing)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//Gebruikt de EBO
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //element tekenen

        // pollevents en swapbuffers
        glfwSwapBuffers(window);
        glfwPollEvents();
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