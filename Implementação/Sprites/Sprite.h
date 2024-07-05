#pragma once
#include <iostream>
#include <string>
#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using namespace std;
using namespace glm;

class Sprite
{
public:
    Sprite(GLuint texID, vec3 pos, vec3 escala, Shader* shader, float speed, float ang = 0.0, bool mirrored = false);
    virtual ~Sprite();

    void setShader(Shader* shader);
    virtual void draw();
    void mirrorIt(bool mirrored);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

protected:
    void update();

    GLuint VAO;
    GLuint texID;

    glm::vec3 pos, scale;
    float ang, speed;
    bool isMirrored;

    Shader* shader;
};
