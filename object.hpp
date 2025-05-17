//
// Created by James Pickering on 3/15/25.
//

#pragma once

#include "lib/graphics/entity.hpp"
#include "lib/graphics/shader.hpp"

#include <functional>

struct Camera;
struct Cursor;

enum class Axis {
    X,
    Y,
    Z
};

struct Face {
    glm::vec3 center;
    Axis axis;
};


//
// struct Object : Entity {
//     // explicit Object();
//     ~Object() override = default;
//
//     // TODO: reimplement this
//     // auto setRotationDelta(glm::vec2 rotate, Cursor& cursor) -> void;
//     // auto setRotation(glm::vec2 rotate) -> void;
//     // auto render(Shader shader, const Camera& camera) const -> void override;
//
//     // auto setCursorCoords(Cursor& cursor, const Camera& camera) -> void;
//     // auto setPosition(glm::vec3 pos) -> void;
//     // auto setSize(glm::vec3 size) -> void;
//     // auto setFillColor(glm::vec4 color) -> void;
//     // auto setUseTexture(bool useTexture) -> void;
//
//     // unsigned int texture;
//
//     // auto containsCursor() -> bool;
//     // auto commitRotation() -> void;
//     // auto setDragging(bool dragging) -> void;
//
//     // [[nodiscard]] auto isDragging() const -> bool;
//     // [[nodiscard]] auto getRotation() const -> glm::vec2;
//
// protected:
//     // auto updateModel() -> void;
// //
// // private:
// //
// //     glm::vec2 _crot;
// //     // glm::vec3 _pos;
// //     // glm::vec3 _size;
// //     glm::vec4 _fillColor;
// //
// //     // glm::mat4 _model;
// //     //
// //     // glm::vec3 _edge;
// //     bool _activeEdge;
// //     //bool _dragging = false;
// //     bool _useTexture = false;
//     // bool _useMultiTextures = false;
// };
