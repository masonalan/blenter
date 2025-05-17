//
// Created by James Pickering on 3/15/25.
//

#include "cursor_entity.hpp"

#include "lib/graphics/camera.hpp"
#include "lib/graphics/cursor.hpp"
#include "shapes.hpp"
#include "texture.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>



// CursorEntity::CursorEntity() {
//     auto type = CursorType::Pointer;
//     while (type != CursorType::None) {
//         _textures[type] = Texture::fromPng(getImagePath(type));
//         type = static_cast<CursorType>(static_cast<int>(type) + 1);
//     }
// }

// auto CursorEntity::bindTextures() const -> void {
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, _textures.at(Cursor::instance().cursorAction));
// }
