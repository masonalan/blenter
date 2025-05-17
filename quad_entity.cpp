//
// Created by James Pickering on 3/15/25.
//

#include "quad_entity.hpp"

#include "lib/graphics/camera.hpp"
#include "lib/graphics/cursor.hpp"
#include "shapes.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// QuadEntity::QuadEntity() {
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//     const auto&& indices = (unsigned int[]){
//         0, 1, 3,// first triangle
//         1,
//         2,
//         3// second triangle
//     };
//
//     unsigned int ebo;
//
//     glGenVertexArrays(1, &vao);
//     glGenBuffers(1, &ebo);
//     glBindVertexArray(vao);
//     glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::rectangle());
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//     glEnableVertexAttribArray(0);
//     glEnableVertexAttribArray(1);
//     glEnableVertexAttribArray(2);
// }

// QuadEntity::~QuadEntity() = default;

// auto QuadEntity::update(glm::vec3 pos, bool mouseDown) -> void {
//     this->_pos = pos;
//     grabbing = mouseDown;
// }

// auto QuadEntity::bindTextures() const -> void {
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, texture);
// }

// auto QuadEntity::setPos(glm::vec3 pos) -> void {
//     _pos = pos;
// }
//
// auto QuadEntity::setSize(glm::vec3 size) -> void {
//     _size = size;
// }

// auto QuadEntity::mouseEnter(glm::vec2 pos) -> void {
//     // TODO: move to contains()
//     _focused = transform.pos.x + transform.size.x / 2.f > pos.x &&
//                transform.pos.x - transform.size.x / 2.f < pos.x &&
//                transform.pos.y + transform.size.y / 2.f > pos.y &&
//                transform.pos.y - transform.size.y / 2.f < pos.y;
// }
//
// auto QuadEntity::mousePressed() -> void {
//     if (_focused) {
//         if (onMousePressed) {
//             onMousePressed();
//         }
//     }
// }

// auto QuadEntity::render(const Shader shader, const Camera& camera) const -> void {
//     auto model = glm::mat4{1.f};
//     model = translate(model, _pos);
//     model = scale(model, _size);
//
//     shader.setMat4("model", model);
//     shader.setVec3("viewPos", camera.position());
//     shader.setBool("useTexture", true);
//     shader.setBool("useMultiTextures", false);
//     shader.setBool("focused", _focused);
//     shader.setBool("selected", _selected);
//
//     bindTextures();
//     glBindVertexArray(vao);
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//     glBindTexture(GL_TEXTURE_2D, 0);
//
//     shader.setBool("focused", false);
//     shader.setBool("selected", false);
// }

// auto QuadEntity::setTexture(unsigned int tex) -> void {
//     texture = tex;
// }

// auto QuadEntity::containsCursor() const -> bool {
//     const auto& pos = Cursor::instance().screenSpacePos;
//     return pos.x > transform.pos.x - transform.size.x / 2.f &&
//            pos.x < transform.pos.x + transform.size.x / 2.f &&
//            pos.y > transform.pos.y - transform.size.y / 2.f &&
//            pos.y < transform.pos.y + transform.size.y / 2.f;
// }

// auto QuadEntity::setSelected(bool selected) -> void {
//     _selected = selected;
// }
