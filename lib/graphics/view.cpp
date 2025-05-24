//
// Created by James Pickering on 3/17/25.
//

#include "view.hpp"

#include "../../block_entity.hpp"
#include "../../engine.hpp"
#include "../../objects_scene.hpp"
#include "color.hpp"
#include "event.hpp"
#include "window.hpp"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

View::View(Window& window, Engine& engine) :
    _engine(engine),
    _window{window},
    _shader{"main_shader.vert", "main_shader.frag"} {
    _window.onScroll = [this](auto distance) {
        getCurrentScene()->wheelScrolled(distance);
        _uiScene->wheelScrolled(distance);
    };

    _window.onCursorMove = [this](auto pos) {
        move(Cursor::instance(), pos);

        auto ev = Event{};
        _uiScene->mouseMoved(ev);
        if (ev.isAccepted()) {
            return;
        }
        getCurrentScene()->mouseMoved(ev);
    };

    _window.onResize = [this](auto size) {
        setScreenSpacePosition(Cursor::instance(), size);
        getCurrentScene()->windowResized(size);
        _uiScene->windowResized(size);
    };

    _window.onProcessInput = [this] {
        const auto win = _window.getGlfwWindow();
        setPressed(Cursor::instance(), glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
        getCurrentScene()->processInput();

        //_engine.shiftPressed = glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        _uiScene->processInput();
    };

    Cursor::instance().onPress = [this] {
        auto ev = Event{};
        _uiScene->mousePressed(ev);
        getCurrentScene()->mousePressed(ev);
    };

    Cursor::instance().onMouseUp = [this] {
        auto ev = Event{};
        _uiScene->mouseReleased(ev);
        getCurrentScene()->mouseReleased(ev);
    };

    _shader.use();
    _shader.setInt("tex1", 0);
    _shader.setInt("tex2", 1);
    _shader.setInt("tex3", 2);
}

View::~View() = default;

auto View::update() -> void {
    updateCursor(Cursor::instance());
    if (getCurrentScene()->onTick) {
        getCurrentScene()->onTick();
    }
    if (_uiScene->onTick) {
        _uiScene->onTick();
    }
}

auto View::render() const -> void {
    glClearColor(color::creme.r, color::creme.g, color::creme.b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // -------------------------------------------------------------
    // Render 3D
    // -------------------------------------------------------------

    _scenes.at(_currentScene)->render();

    _uiScene->render();

    // _shader.use();
    // _shader.setMat4("view", _cam2d.view());
    // _shader.setMat4("proj", _cam2d.projection());
}

auto View::getBlockEntities() -> std::vector<std::unique_ptr<Entity>>& {
    return _blockEntities;
}

auto View::getShader() const -> const Shader& {
    return _shader;
}

auto View::getWindow() const -> const Window& {
    return _window;
}

auto View::getCurrentScene() const -> Scene* {
    return _scenes.at(_currentScene).get();
}

auto View::setUiScene(std::unique_ptr<Scene> scene) -> void {
    _uiScene = std::move(scene);
}
