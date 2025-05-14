//
// Created by James Pickering on 3/15/25.
//

#include "CursorEntity.hpp"

#include "texture.hpp"
#include "camera.hpp"
#include "shapes.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CursorEntity::CursorEntity() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture = Texture::fromPng("cursor_pointer.png");
    grabTex = Texture::fromPng("cursor_grabber.png");

    const auto &&indices = (unsigned int[]){
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    unsigned int ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::rectangle());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

auto CursorEntity::update(glm::vec2 pos, bool mouseDown) -> void {
    this->pos = pos * 2.f;
    grabbing = mouseDown;
}

auto CursorEntity::render(Shader shader, const Camera &camera) const noexcept -> void {
    auto model = glm::mat4{1.f};
    //
    model = glm::translate(model, glm::vec3{pos, -2.f});
    model = glm::scale(model, glm::vec3{0.1f, 0.1f, 1.f});


    shader.setMat4("model", model);
    shader.setVec3("viewPos", camera.position());

    glActiveTexture(GL_TEXTURE0);
    if (grabbing) {
        glBindTexture(GL_TEXTURE_2D, grabTex);
    } else {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
