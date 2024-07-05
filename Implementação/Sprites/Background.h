#pragma once
#include "Sprite.h"

class Background : public Sprite
{
public:
    Background(GLuint texID, glm::vec3 pos, glm::vec3 scale, Shader* shader)
        : Sprite(texID, pos, scale, shader, 0.0f) {}

    void draw();
};
