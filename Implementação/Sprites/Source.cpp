#include <iostream>
#include <string>
#include <assert.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

#include "Shader.h"

#include "CharacterController.h"
#include "Background.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLuint loadTexture(string texturePath);

const GLuint WIDTH = 800, HEIGHT = 600;

CharacterController* player;
Background* background;

int main()
{
    glfwInit();

    srand((int)glfwGetTime());

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Falha ao inicializar a GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("../shaders/tex_vert.glsl", "../shaders/tex_frag.glsl");

    GLuint idleTexture = loadTexture("../../Textures/characters/Archer/Idle_2.png");
    GLuint runTexture = loadTexture("../../Textures/characters/Archer/Run.png");
    GLuint backgroundTexture = loadTexture("../../Textures/backgrounds/Battleground3/Bright/Battleground3.png");

    player = new CharacterController(idleTexture, runTexture, glm::vec3(400.0, 200.0, 0.0), glm::vec3(128, 128, 1.0), &shader, 6.0, 180.0);
    background = new Background(backgroundTexture, glm::vec3(400.0, 300.0, 0.0), glm::vec3(800.0, 600.0, 1.0), &shader);

    glActiveTexture(GL_TEXTURE0);

    shader.Use();

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    shader.setMat4("projection", glm::value_ptr(projection));

    shader.setInt("texBuffer", 0);

    float lastTime = glfwGetTime();
    float deltaTime;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        player->updateAnimation(deltaTime);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        background->draw();
        player->draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    player->handleInput(key, action);
}

GLuint loadTexture(string texturePath)
{
    GLuint texID;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;
}
