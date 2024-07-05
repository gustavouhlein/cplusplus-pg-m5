#include "Sprite.h"

Sprite::Sprite(GLuint texID, vec3 pos, vec3 scale, Shader* shader, float speed, float ang, bool mirrored)
{
    this->texID = texID;
    this->pos = pos;
    this->ang = ang;
    this->scale = scale;
    this->isMirrored = mirrored;
    this->speed = speed;
    setShader(shader);

    GLfloat vertices[] = {
        // x     y     z     r    g    b    s    t
        -0.5,  0.5,  0.0,  1.0, 0.0, 0.0, 0.0, 1.0,  // v0
        -0.5, -0.5,  0.0,  1.0, 0.0, 0.0, 0.0, 0.0,  // v1
         0.5,  0.5,  0.0,  1.0, 0.0, 0.0, 1.0, 1.0,  // v2
         0.5, -0.5,  0.0,  1.0, 0.0, 0.0, 1.0, 0.0   // v3
    };

    GLuint VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &VAO);
}

void Sprite::setShader(Shader* shader)
{
    this->shader = shader;
}

void Sprite::draw()
{
    update();
    glBindTexture(GL_TEXTURE_2D, texID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void Sprite::update()
{
    mat4 model = glm::mat4(1);
    model = translate(model, pos);
    if (isMirrored)
        model = rotate(model, radians(180.0f), vec3(0.0, 1.0, 0.0));
    model = rotate(model, radians(ang), vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, scale);
    shader->setMat4("model", glm::value_ptr(model));
}

void Sprite::mirrorIt(bool mirrored)
{
    this->isMirrored = mirrored;
}

void Sprite::moveLeft()
{
    if (isMirrored)
        isMirrored = false;
    pos.x -= speed;
}

void Sprite::moveRight()
{
    if (!isMirrored)
        isMirrored = true;
    pos.x += speed;
}

void Sprite::moveUp()
{
    pos.y += speed;
}

void Sprite::moveDown()
{
    pos.y -= speed;
}
