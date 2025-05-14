//
// Created by James Pickering on 3/15/25.
//

#pragma once

#include "shader.hpp"

#include <glm/vec2.hpp>

struct Camera;

struct CursorEntity {
    CursorEntity();

    auto update(glm::vec2 pos, bool mouseDown) -> void;

    auto render(Shader shader, const Camera &camera) const noexcept -> void;

private:
    unsigned int vao;
    unsigned int texture;
    unsigned int grabTex;

    glm::vec2 pos;

    bool grabbing = false;


};
