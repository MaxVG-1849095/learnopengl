#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "model.h"

float camX = 0.0f;
float camZ = 0.0f;
Camera cam = Camera();
bool wireframing = false;
bool flashlight = false;
//prototypes
unsigned int loadTexture(const char *path);
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

    string name ;
    std::ifstream dataFile("models/backpack/backpack.txt");
    while (!dataFile.fail() && !dataFile.eof() )
    {
          dataFile >> name ;
          cout << name << endl;
    }

    // build and compile shaders
    // -------------------------
    Shader ourShader("modelShader.vs", "modelShader.fs");

    // load models
    // -----------
    Model ourModel("models/backpack/backpack.obj");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    float rotateAngle = 0.0f;

    while (!glfwWindowShouldClose(window)) // render loop
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // perspective (fov, screensize, close, far) close en far zijn standardised
        glm::mat4 view = cam.lookAt();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

         if (wireframing)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

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
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) // p = print message
    {
        std::cout << "swapping flashlight" << std::endl;
        flashlight = !flashlight;
        std::cout << flashlight << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // p = print message
    {
        cam.goForward();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // p = print message
    {
        cam.goBackward();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // p = print message
    {
        cam.goRight();
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // p = print message
    {
        cam.goLeft();
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // p = print message
    {
        cam.pitchUp();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // p = print message
    {
        cam.pitchDown();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // p = print message
    {
        cam.yawUp();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // p = print message
    {
        cam.yawDown();
    }
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}