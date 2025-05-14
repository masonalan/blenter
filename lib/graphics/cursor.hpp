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
    Cursor() = default;

    auto updateClipSpacePosition() {
        _lastClipSpacePos = _clipSpacePos;
        _clipSpacePos = glm::vec2{_screenSpacePos / _viewportSize * 2.f};
        _clipSpacePos = {std::fmin(1.f, std::fmax(-1.f, _clipSpacePos.x)),
                         std::fmin(1.f, std::fmax(-1.f, _clipSpacePos.y))};
    }

    auto setViewport(glm::vec2 size) {
        _viewportSize = size;
    }

    auto setScreenSpacePosition(glm::vec2 position) {
        _screenSpacePos = position;
        updateClipSpacePosition();
    }

    auto setCursorAction(CursorType action) {
        _cursorAction = action;
    }

    [[nodiscard]] auto getClipSpacePosition() const {
        return _clipSpacePos;
    }

    [[nodiscard]] auto getScreenSpacePosition() const {
        return _screenSpacePos;
    }

    auto setPressed(const bool pressed) {
        if (!_pressed && pressed) {
            _clipSpaceMouseDownAt = _screenSpacePos;
            if (_onPress) {
                _onPress();
            }
        } else if (_pressed && !pressed) {
            if (_onMouseUp) {
                _onMouseUp();
            }
        }
        _pressed = pressed;
    }

    auto setOnMouseDown(auto&& fn) {
        _onPress = fn;
    }

    auto setOnMouseUp(auto&& fn) {
        _onMouseUp = fn;
    }

    auto update() {
        _lastClipSpacePos = _clipSpacePos;
    }

    [[nodiscard]] auto getClipSpaceDelta() const {
        return _clipSpacePos - _lastClipSpacePos;
    }

    [[nodiscard]] auto toWorldSpace(const glm::vec2 clipSpace, const Camera& cam) const {
        return cam.invProjView() * glm::vec4{clipSpace, 0.f, 1.f};
    }

    [[nodiscard]] auto getCursorAction() const {
        return _cursorAction;
    }

    [[nodiscard]] auto isPressed() const {
        return _pressed;
    }

    [[nodiscard]] auto posWhenLastPressed() const {
        return _clipSpaceMouseDownAt;
    }

    auto move(glm::vec2 posScreenSpace) {
        if (_isFirstMove) {
            _lastPosScreenSpace = posScreenSpace;
            _isFirstMove = false;
        }

        const auto delta = posScreenSpace - _lastPosScreenSpace;

        _screenSpacePos.x += delta.x;
        _screenSpacePos.y -= delta.y;
        _lastPosScreenSpace = posScreenSpace;

        updateClipSpacePosition();

        std::cout << "Screen space: " << _screenSpacePos.x << ", " << _screenSpacePos.y << std::endl;
    }

private:
    glm::vec2 _viewportSize;
    glm::vec2 _screenSpacePos;
    glm::vec2 _clipSpacePos;
    glm::vec2 _lastClipSpacePos;
    glm::vec2 _clipSpaceMouseDownAt;
    glm::vec2 _lastPosScreenSpace;

    CursorType _cursorAction = CursorType::Pointer;

    bool _pressed = false;
    bool _isFirstMove = true;

    std::function<void()> _onPress;
    std::function<void()> _onMouseUp;
};
