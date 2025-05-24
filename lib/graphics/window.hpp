//
// Created by James Pickering on 3/17/25.
//

#pragma once

#include <glm/vec2.hpp>

#include <functional>
#include <string>

class GLFWwindow;
struct Window;

struct Window {
    std::function<void(glm::ivec2)> onResize;
    std::function<void(float distance)> onScroll;
    std::function<void(glm::vec2 pos)> onCursorMove;
    std::function<void()> onProcessInput;

    std::string _title;
    GLFWwindow* _window;
    glm::ivec2 _size;
    bool _mousePressedOnce = false;

public:
    Window(std::string title, glm::ivec2 size);
    ~Window();

    auto processInput() const -> void;

    [[nodiscard]] auto getGlfwWindow() const -> GLFWwindow*;
    [[nodiscard]] auto getTitle() const -> const std::string&;
    [[nodiscard]] auto getSize() const -> glm::ivec2;
    [[nodiscard]] auto isMousePressedOnce() const -> bool;

    auto setSize(glm::ivec2 size) -> void;
    auto setMousePressedOnce(bool value) -> void;
};
