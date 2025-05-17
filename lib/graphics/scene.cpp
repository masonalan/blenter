//
// Created by James Pickering on 3/18/25.
//

#include "scene.hpp"

#include "camera.hpp"
#include "entity.hpp"
#include "mouse.hpp"

#include "view.hpp"

Scene::Scene(View& view) :
    _view{view},
    cam{ProjectionType::Orthographic} {}

Scene::~Scene() = default;

auto Scene::render() const -> void {
    const auto& shader = getView().getShader();

    shader.use();
    shader.setMat4("view", cam.view());
    shader.setMat4("proj", cam.projection());

    for (const auto& entity : _entities) {
        renderEntity(*entity, shader, cam);
    }
}

auto Scene::mouseMoved(Event& event) const -> void {
    for (auto& entity : _entities) {
        cursorMoved(*entity, Cursor::instance(), cam);
        handleMouseMoved(*entity, Cursor::instance());
        if (event.isAccepted()) {
            break;
        }
    }
}

auto Scene::mousePressed() const -> void {
    for (auto& entity : _entities) {
        handleMousePressed(*entity, Cursor::instance());
    }
}

auto Scene::mouseReleased() const -> void {
    for (auto& entity : _entities) {
        handleMouseReleased(*entity, Cursor::instance());
    }
}

auto Scene::getView() -> View& {
    return _view;
}

auto Scene::getView() const -> const View& {
    return _view;
}

auto Scene::update() -> void {
}

auto Scene::wheelScrolled(float offset) -> void {
    if (flags & CameraZoomsOnScroll) {
        cam.zoom(offset);
    }
}

auto Scene::windowResized(glm::ivec2 size) -> void {
    cam.setSize(size);
}

auto Scene::processInput() -> void {
}
