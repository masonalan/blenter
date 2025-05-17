//
// Created by James Pickering on 3/15/25.
//

#include "object.hpp"

#include "lib/graphics/camera.hpp"
#include "lib/graphics/cursor.hpp"
#include "lib/graphics/shader.hpp"
#include "shapes.hpp"
#include "texture.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
//
// Object::Object() {
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//     glGenVertexArrays(1, &_vao);
//     glBindVertexArray(_vao);
//     glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer::cube());
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//     glEnableVertexAttribArray(0);
//     glEnableVertexAttribArray(1);
//     glEnableVertexAttribArray(2);
// }

// auto Object::setRotationDelta(glm::vec2 rotate, Cursor& cursor) -> void {
//     if (!isDragging()) {
//         _rotation = _crot + rotate;
//     } else {
//         if (_edge.x != 0) {
//             _size.x += delta(cursor.clipSpacePos, cursor.lastClipSpacePos).x * 2;
//         } else if (_edge.y != 0) {
//             _size.y += delta(cursor.clipSpacePos, cursor.lastClipSpacePos).x * 2;
//         } else if (_edge.z != 0) {
//             _size.z += delta(cursor.clipSpacePos, cursor.lastClipSpacePos).x * 2;
//         }
//     }
//
//     updateModel();
// }
//
// auto Object::setRotation(glm::vec2 rotate) -> void {
//     _rotation = rotate;
//     // updateModel();
// }
//
// auto Object::getRotation() const -> glm::vec2 {
//     return _rotation;
// }

// auto bindTextures(const std::vector<unsigned int>& textures) -> void {
//     for (auto i = 0; i < textures.size(); i++) {
//         glActiveTexture(GL_TEXTURE0 + i);
//         glBindTexture(GL_TEXTURE_2D, textures.at(i));
//     }
// }

// auto Object::render(Shader shader, const Camera& camera) const -> void {
//     shader.use();
//
//     glBindVertexArray(_vao);
//
//     shader.setBool("useTexture", _useTexture);
//     shader.setBool("useMultiTextures", true);
//     if (_useTexture) {
//         bindTextures(textures);
//     } else {
//         glBindTexture(GL_TEXTURE_2D, 0);
//         shader.setVec4("fillColor", _fillColor);
//     }
//
//     shader.setMat4("model", _model);
//     shader.setVec3("viewPos", camera.position());
//     shader.setVec3("edge", _edge);
//
//     glDrawArrays(GL_TRIANGLES, 0, 36);
//     auto error = glGetError();
//
//     switch (error) {
//     case GL_INVALID_ENUM:
//         std::cout << "Invalid enum" << std::endl;
//         break;
//     case GL_INVALID_VALUE:
//         std::cout << "Invalid value" << std::endl;
//         break;
//     case GL_INVALID_OPERATION:
//         std::cout << "Invalid operation" << std::endl;
//         break;
//     case 0:
//         break;
//     default:
//         std::cout << "Unknown error" << std::endl;
//         break;
//     }
// }
//
// auto Object::updateModel() -> void {
//     // _model = glm::mat4{1.f};
//     //
//     // _model = glm::translate(_model, _pos);
//     // _model = glm::rotate(_model, glm::radians(_rotation.x), glm::vec3(0.f, 1.0f, 0.f));
//     // _model = glm::rotate(_model, glm::radians(_rotation.y), glm::vec3(1., 0.f, 0.f));
//     // _model = glm::scale(_model, _size);
// }

// auto Object::containsCursor() -> bool {
//     return _activeEdge;
// }

// auto Object::setCursorCoords(Cursor& cursor, const Camera& camera) -> void {
//     if (flags & Dragging || cursor.pressed) {
//         return;
//     }
//     edge = glm::vec3{0.0f, 0.0f, 0.0f};
//     _activeEdge = false;
//     cursor.cursorAction = CursorType::Hand;
//     auto lastConverted = glm::vec4{-100};
//
//     const auto faces = std::vector{
//         Face{glm::vec3{0.0f, 0.0f, 0.5f}, Axis::Z},
//         Face{glm::vec3{-0.5f, 0.f, 0.0f}, Axis::X},
//         Face{glm::vec3{0.f, -0.5f, 0.0f}, Axis::Y},
//     };
//
//     for (const auto& face : faces) {
//         auto bounds = std::vector<glm::vec4>{};
//         switch (face.axis) {
//         case Axis::X:
//             bounds = std::vector{glm::vec4{face.center.x, face.center.y - 0.5f, face.center.z - 0.5f, 1.f},
//                                  glm::vec4{face.center.x, face.center.y + 0.5f, face.center.z - 0.5f, 1.f},
//                                  glm::vec4{face.center.x, face.center.y + 0.5f, face.center.z + 0.5f, 1.f},
//                                  glm::vec4{face.center.x, face.center.y - 0.5f, face.center.z + 0.5f, 1.f}};
//             break;
//         case Axis::Y:
//             bounds = std::vector{glm::vec4{face.center.x - 0.5f, face.center.y, face.center.z - 0.5f, 1.f},
//                                  glm::vec4{face.center.x + 0.5f, face.center.y, face.center.z - 0.5f, 1.f},
//                                  glm::vec4{face.center.x + 0.5f, face.center.y, face.center.z + 0.5f, 1.f},
//                                  glm::vec4{face.center.x - 0.5f, face.center.y, face.center.z + 0.5f, 1.f}};
//             break;
//         case Axis::Z:
//             bounds = std::vector{glm::vec4{face.center.x - 0.5f, face.center.y - 0.5f, face.center.z, 1.f},
//                                  glm::vec4{face.center.x + 0.5f, face.center.y - 0.5f, face.center.z, 1.f},
//                                  glm::vec4{face.center.x + 0.5f, face.center.y + 0.5f, face.center.z, 1.f},
//                                  glm::vec4{face.center.x - 0.5f, face.center.y + 0.5f, face.center.z, 1.f}};
//             break;
//         }
//
//         auto convertedFace = std::vector{camera.projection() * camera.view() * model * bounds.at(0),
//                                          camera.projection() * camera.view() * model * bounds.at(1),
//                                          camera.projection() * camera.view() * model * bounds.at(2),
//                                          camera.projection() * camera.view() * model * bounds.at(3)};
//
//         for (auto& c : convertedFace) {
//             c.x /= c.w;
//             c.y /= c.w;
//             c.z /= c.w;
//         }
//
//         const auto cursorPos = cursor.clipSpacePos;
//         auto isMatch = false;
//         // switch (face.axis) {
//         // case Axis::Z:
//         isMatch = isPointInPolygon(cursorPos, convertedFace);
//         //if (cursorPos.x > convertedFace.at(0).x && cursorPos.x < convertedFace.at(1).x) {}
//         //     break;
//         // default:
//         //     break;
//         // }
//
//         //std::cout << convertedFace.at(0).x << ", " << convertedFace.at(0).y << ", " << convertedFace.at(0).z << std::endl;
//         // std::cout << convertedFace.at(0).x << ", " << convertedFace.at(0).y << ", " << convertedFace.at(0).z << std::endl;
//
//         //std::cout << cursorPos.x << ", " << cursorPos.y << std::endl;
//
//         // switch (face.axis) {
//         // default:
//         //     isMatch = convertedFace.at(0).x < cursorPos.x && convertedFace.at(1).x > cursorPos.x &&
//         //               convertedFace.at(0).y < cursorPos.y && convertedFace.at(2).y > cursorPos.y;
//         //     break;
//         // }
//         if (isMatch) {
//             cursor.cursorAction = CursorType::Pointer;
//             edge = face.center;
//             _activeEdge = true;
//         }
//     }
// }

// auto Object::setPosition(const glm::vec3 pos) -> void {
//     _pos = pos;
//     updateModel();
// }
//
// auto Object::setSize(const glm::vec3 size) -> void {
//     _size = size;
//     updateModel();
// }

// auto Object::setFillColor(const glm::vec4 color) -> void {
//     _fillColor = color;
//     _useTexture = false;
// }

// auto Object::commitRotation() -> void {
//     _crot = transform.rot;
// }
//
// auto Object::setDragging(const bool dragging) -> void {
//     _dragging = dragging;
// }

// auto Object::setUseTexture(const bool useTexture) -> void {
//     _useTexture = useTexture;
// }

// auto Object::isDragging() const -> bool {
//     return _dragging;
// }
