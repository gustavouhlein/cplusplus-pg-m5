#include "Background.h"

void Background::draw()
{
    mat4 model = glm::mat4(1);
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, radians(180.0f), vec3(1.0, 0.0, 0.0));
    shader->setMat4("model", glm::value_ptr(model));

    shader->Use();
    shader->setVec2("offset", glm::vec2(0.0f, 0.0f));
    shader->setFloat("frameWidth", 1.0f);

    glBindTexture(GL_TEXTURE_2D, texID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
