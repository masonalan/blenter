//
// Created by James Pickering on 3/16/25.
//

#pragma once

#include "lib/graphics/entity.hpp"
#include "lib/graphics/shader.hpp"

#include <glm/vec2.hpp>

#include <functional>

struct Camera;
struct Cursor;
//
// struct QuadEntity : Entity {
//     // explicit QuadEntity();
//     ~QuadEntity() override;
//
//     // auto update(glm::vec2 pos, bool mouseDown) -> void;
//     // auto render(Shader shader, const Camera& camera) const -> void override;
//     // auto setTexture(unsigned int tex) -> void;
//     // auto setPos(glm::vec3 pos) -> void;
//     // auto setSize(glm::vec3 size) -> void;
//     auto setSelected(bool selected) -> void;
//
//     auto mouseEnter(glm::vec2 pos) -> void;
//     auto mousePressed() -> void;
//
//     // [[nodiscard]] auto containsCursor() const -> bool override;
//
//     // virtual auto bindTextures() const -> void;
//
//     std::function<void()> onMousePressed;
//
//     bool _focused = false;
//
// protected:
//
//     // glm::vec3 _pos;
//     // glm::vec3 _size;
//
//     bool grabbing = false;
//
//
//     bool _selected = false;
// };
