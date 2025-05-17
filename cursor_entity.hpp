//
// Created by James Pickering on 3/15/25.
//

#pragma once

#include "lib/graphics/cursor_type.hpp"
#include "quad_entity.hpp"

#include <unordered_map>

struct Camera;
struct Cursor;

constexpr auto getImagePath(CursorType type) -> const char* {
    switch (type) {
    case CursorType::Pointer:
        return "cursor_pointer.png";
    case CursorType::Expand:
        return "cursor_resize.png";
    case CursorType::Fist:
        return "cursor_grabber.png";
    case CursorType::Hand:
        return "cursor_hand.png";
    case CursorType::Pinch:
        return "cursor_resizer.png";
    default:
        throw std::runtime_error("Cursor type not recognized");
    }
}

// struct CursorEntity : QuadEntity {
//     explicit CursorEntity();
//
//     // auto bindTextures() const -> void override;
//
// private:
//     std::unordered_map<CursorType, unsigned int> _textures{};
// };
