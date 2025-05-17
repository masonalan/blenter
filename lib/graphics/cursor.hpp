//
// Created by James Pickering on 3/16/25.
//

#pragma once

#include "camera.hpp"
#include "cursor_type.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <ostream>

struct Cursor {
    static auto instance() -> Cursor& {
        return _instance;
    }

private:
    static Cursor _instance;

public:
    glm::vec2 viewportSize;
    glm::vec2 screenSpacePos;
    glm::vec2 clipSpacePos;
    glm::vec2 lastClipSpacePos;
    glm::vec2 clipSpaceMouseDownAt;
    glm::vec2 lastPosScreenSpace;

    CursorType cursorType = CursorType::Pointer;

    bool pressed = false;
    bool isFirstMove = true;

    std::function<void()> onPress;
    std::function<void()> onMouseUp;
};

inline auto updateClipSpacePosition(Cursor& cur) {
    // Update the clip position

    cur.lastClipSpacePos = cur.clipSpacePos;
    cur.clipSpacePos = glm::vec2{cur.screenSpacePos / cur.viewportSize * 2.f};
    cur.clipSpacePos = {std::fmin(1.f, std::fmax(-1.f, cur.clipSpacePos.x)),
                        std::fmin(1.f, std::fmax(-1.f, cur.clipSpacePos.y))};
}

inline auto setScreenSpacePosition(Cursor& cur, glm::vec2 position) {
    // Set and update screen space position

    cur.screenSpacePos = position;
    updateClipSpacePosition(cur);
}

inline auto move(Cursor& cur, glm::vec2 posScreenSpace) {
    // Move the cursor to a position in screen space

    if (cur.isFirstMove) {
        cur.lastPosScreenSpace = posScreenSpace;
        cur.isFirstMove = false;
    }

    const auto delta = posScreenSpace - cur.lastPosScreenSpace;

    cur.screenSpacePos.x += delta.x;
    cur.screenSpacePos.y -= delta.y;
    cur.lastPosScreenSpace = posScreenSpace;

    updateClipSpacePosition(cur);
}

inline auto setPressed(Cursor& cur, const bool pressed) {
    // Set the cursor as pressed and handle calling any callbacks
    // that are set for the appropriate change

    if (!cur.pressed && pressed) {
        cur.clipSpaceMouseDownAt = cur.screenSpacePos;
        cur.pressed = true;
        if (cur.onPress) {
            cur.onPress();
        }
    } else if (cur.pressed && !pressed) {
        cur.pressed = false;
        if (cur.onMouseUp) {
            cur.onMouseUp();
        }
    }
}

inline auto toWorldSpace(const glm::vec2 clipSpace, const Camera& cam) {
    // Converts a position in clip space to a position in world space

    return cam.invProjView() * glm::vec4{clipSpace, 0.f, 1.f};
}

inline auto delta(const glm::vec2 start, const glm::vec2 end) {
    // Gets the delta between two vectors

    return end - start;
}

inline auto updateCursor(Cursor& cur) {
    // Set the cursors last pos to the current pos
    cur.lastClipSpacePos = cur.clipSpacePos;
}