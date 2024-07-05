#include "CharacterController.h"

void CharacterController::handleInput(int key, int action)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_W:
        case GLFW_KEY_UP:
            moveUp();
            animationIndex = 1;
            break;
        case GLFW_KEY_S:
        case GLFW_KEY_DOWN:
            moveDown();
            animationIndex = 1;
            break;
        case GLFW_KEY_A:
        case GLFW_KEY_LEFT:
            moveLeft();
            animationIndex = 1;
            break;
        case GLFW_KEY_D:
        case GLFW_KEY_RIGHT:
            moveRight();
            animationIndex = 1;
            break;
        default:
            animationIndex = 0;
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        animationIndex = 0;
    }
}

void CharacterController::updateAnimation(float deltaTime)
{
    time += deltaTime;
    if (time >= frameTime)
    {
        time = 0.0f;
        frameIndex = (frameIndex + 1) % (animationIndex == 0 ? nFramesIdle : nFramesRun);
    }

    int currentFrameCount = (animationIndex == 0 ? nFramesIdle : nFramesRun);
    float ds = 1.0f / currentFrameCount;
    float offsetS = frameIndex * ds;

    if (animationIndex == 0)
    {
        texID = idleTexID;
        shader->setFloat("frameWidth", 1.0f / nFramesIdle);
    }
    else
    {
        texID = runTexID;
        shader->setFloat("frameWidth", 1.0f / nFramesRun);
    }

    shader->setVec2("offset", glm::vec2(offsetS, 0.0f));

}

void CharacterController::draw()
{
    update();
    shader->Use();
    shader->setVec2("offset", glm::vec2(frameIndex * (1.0f / (animationIndex == 0 ? nFramesIdle : nFramesRun)), 0.0f));
    shader->setFloat("frameWidth", 1.0f / (animationIndex == 0 ? nFramesIdle : nFramesRun));

    glBindTexture(GL_TEXTURE_2D, texID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
