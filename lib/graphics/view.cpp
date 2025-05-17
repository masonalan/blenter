//
// Created by James Pickering on 3/17/25.
//

#include "view.hpp"

#include "../../block_entity.hpp"
#include "../../engine.hpp"
#include "../../objects_scene.hpp"
#include "event.hpp"
#include "window.hpp"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

View::View(Window& window, Engine& engine) :
    _window{window},
    _shader{"main_shader.vert", "main_shader.frag"} {// _cam2d{ProjectionType::Orthographic} {
    // _cam2d.setSize(window.getSize());

    _window.onScroll = [this](auto distance) {
        getCurrentScene()->wheelScrolled(distance);
        _uiScene->wheelScrolled(distance);
    };

    _window.onCursorMove = [this](auto pos) {
        move(Cursor::instance(), pos);

        auto event = Event{};

        getCurrentScene()->mouseMoved(event);
        _uiScene->mouseMoved(event);
    };

    _window.onResize = [this](auto size) {
        setScreenSpacePosition(Cursor::instance(), size);
        getCurrentScene()->windowResized(size);
        _uiScene->windowResized(size);
    };

    _window.onProcessInput = [this]() {
        const auto win = _window.getGlfwWindow();
        setPressed(Cursor::instance(), glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
        getCurrentScene()->processInput();
        _uiScene->processInput();
    };

    Cursor::instance().onPress = ([this]() {
        //_shader.setBool("mouseDown", true);
        getCurrentScene()->mousePressed();
        _uiScene->mousePressed();
    });

    Cursor::instance().onMouseUp = [this] {
       // _shader.setBool("mouseDown", false);
        getCurrentScene()->mouseReleased();
        _uiScene->mouseReleased();
    };

    _shader.use();
    _shader.setInt("tex1", 0);
    _shader.setInt("tex2", 1);
    _shader.setInt("tex3", 2);
}

View::~View() = default;

auto View::update() -> void {
    // Cursor::instance()::setCursorAction(CursorType::Hand);

    updateCursor(Cursor::instance());
    _scenes.at(_currentScene)->update();
}

auto View::render() const -> void {
    glClearColor(0.95f, 0.99f, 0.9f, 1.f);
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
