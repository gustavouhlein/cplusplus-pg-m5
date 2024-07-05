#pragma once
#include "Sprite.h"
#include <glm/glm.hpp>

class CharacterController : public Sprite
{
public:
    CharacterController(GLuint idleTexID, GLuint runTexID, glm::vec3 pos, glm::vec3 escala, Shader* shader, float speed, float ang = 0.0, bool mirrored = false)
        : Sprite(idleTexID, pos, escala, shader, speed, ang, mirrored), idleTexID(idleTexID), runTexID(runTexID), frameIndex(0), animationIndex(0), time(0.0f) {}

    void handleInput(int key, int action);
    void updateAnimation(float deltaTime);
    void draw() override;

private:
    GLuint idleTexID, runTexID;
    int frameIndex;
    int animationIndex;
    float time;
    const float frameTime = 0.1f;
    const int nFramesIdle = 4;
    const int nFramesRun = 8;
};
