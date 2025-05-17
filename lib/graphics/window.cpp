//
// Created by James Pickering on 3/18/25.
//

#include "window.hpp"

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <GLFW/glfw3.h>

inline auto framebufferSizeCallback(GLFWwindow* window, int width, int height) -> void;
inline auto cursorCallback(GLFWwindow* window, double xPos, double yPos) -> void;
inline auto scrollCallback(GLFWwindow*, double, double yOffset) -> void;

inline auto getWindow(GLFWwindow* window) {
    return static_cast<Window*>(glfwGetWindowUserPointer(window));
}

Window::Window(std::string title, const glm::ivec2 size) :
    _title{std::move(title)},
    _size{size} {
    // ---------------------------------------------------------------------------------------------------------------
    // Initialize GLFW
    //
    // - the first two hints require a certain OpenGL version
    // - the third hint specifies we want to use the core profile
    // - the final one is required for macOS (not sure why)
    // ---------------------------------------------------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // ---------------------------------------------------------------------------------------------------------------
    // Create a window object
    //
    // First we request a window to be created. After that, we make the window we just created the current context.
    // In this project we want to hide the mouse like in Minecraft so we disable the cursor. Then we want to setup
    // all the relevant callbacks.
    // ---------------------------------------------------------------------------------------------------------------
    _window = glfwCreateWindow(size.x, size.y, _title.c_str(), nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, this);
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
    glfwSetCursorPosCallback(_window, cursorCallback);
    glfwSetScrollCallback(_window, scrollCallback);
}

Window::~Window() {
    glfwDestroyWindow(_window);
}

auto Window::processInput() const -> void {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }

    if (onProcessInput) {
        onProcessInput();
    }
}

auto Window::getGlfwWindow() const -> GLFWwindow* {
    return _window;
}

auto Window::getTitle() const -> const std::string& {
    return _title;
}

auto Window::getSize() const -> glm::ivec2 {
    return _size;
}

auto Window::isMousePressedOnce() const -> bool {
    return _mousePressedOnce;
}

auto Window::setSize(const glm::ivec2 size) -> void {
    _size = size;
}

auto Window::setMousePressedOnce(const bool value) -> void {
    _mousePressedOnce = value;
}

inline auto framebufferSizeCallback(GLFWwindow* window, const int width, const int height) -> void {
    glViewport(0, 0, width, height);

    const auto win = getWindow(window);
    win->setSize({width, height});

    if (win->onResize) {
        win->onResize({width, height});
    }
}

inline auto cursorCallback(GLFWwindow* window, const double xPos, const double yPos) -> void {
    if (const auto win = getWindow(window); win->onCursorMove) {
        win->onCursorMove({xPos, yPos});
    }
}

inline auto scrollCallback(GLFWwindow* window, double, const double yOffset) -> void {
    if (const auto win = getWindow(window); win->onScroll) {
        win->onScroll(static_cast<float>(yOffset));
    }
}