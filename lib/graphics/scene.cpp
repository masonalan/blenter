//
// Created by James Pickering on 3/18/25.
//

#include "scene.hpp"

#include "camera.hpp"
#include "entity.hpp"
#include "mouse.hpp"

#include "../../engine.hpp"
#include "view.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>

Scene::Scene(View& view) :
    _view{view},
    cam{ProjectionType::Orthographic} {}

Scene::~Scene() = default;

auto Scene::render() const -> void {
    const auto& shader = getView().getShader();

    shader.use();
    shader.setMat4("view", cam.view());
    shader.setMat4("proj", cam.projection());

    for (const auto& ent : ents) {
        renderEntity(*ent, shader, cam);
    }
}

auto Scene::mouseMoved(Event& ev) -> void {
    if (cam.flags & CF_CursorControlsLookAt) {
        cam.lookAt(Cursor::instance().screenSpacePos.x, -Cursor::instance().screenSpacePos.y);
    }
    for (auto it = ents.rbegin(); it != ents.rend(); it = std::next(it)) {
        const auto& ent = *it;
        if (ev.isAccepted()) {
            break;
        }
        cursorMoved(*ent, Cursor::instance(), cam);
        handleMouseMoved(*ent, Cursor::instance(), ev);
    }
    if (!ev.isAccepted()) {
        if (Cursor::instance().pressed) {
            if (onDrag) {
                onDrag();
            }
            Cursor::instance().cursorType = CursorType::Fist;
        } else {
            Cursor::instance().cursorType = CursorType::Hand;
        }
    }
    if (onMouseMoved) {
        onMouseMoved();
    }
}

auto Scene::mousePressed(Event& ev) const -> void {
    for (auto it = ents.rbegin(); it != ents.rend(); it = std::next(it)) {
        const auto& ent = *it;
        if (ev.isAccepted()) {
            break;
        }
        handleMousePressed(*ent, Cursor::instance(), ev);
    }
    if (!ev.isAccepted()) {
        if (Cursor::instance().pressed) {
            Cursor::instance().cursorType = CursorType::Fist;
        } else {
            Cursor::instance().cursorType = CursorType::Hand;
        }
    }
    if (onMousePressed) {
        onMousePressed();
    }
}

auto Scene::mouseReleased(Event& ev) const -> void {
    for (auto it = ents.rbegin(); it != ents.rend(); it = std::next(it)) {
        const auto& ent = *it;
        if (ev.isAccepted()) {
            break;
        }
        handleMouseReleased(*ent, Cursor::instance(), ev);
    }
    if (!ev.isAccepted()) {
        if (Cursor::instance().pressed) {
            Cursor::instance().cursorType = CursorType::Fist;
        } else {
            Cursor::instance().cursorType = CursorType::Hand;
        }
    }
    if (onMouseReleased) {
        onMouseReleased();
    }
}

auto Scene::getView() -> View& {
    return _view;
}

auto Scene::getView() const -> const View& {
    return _view;
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
    if (cam._projectionType == ProjectionType::Perspective) {
        if (glfwGetKey(_view.getWindow()._window, GLFW_KEY_RIGHT_SHIFT) && !_view._engine.shiftPressed) {
            auto worldPos = toWorldSpace(Cursor::instance().clipSpacePos, cam, 0.81);

            std::cout << "prev cam: " << cam._pos.x << ", " << cam._pos.y << ", " << cam._pos.z << std::endl;
            //worldPos.x *= 2.f;
            std::cout << "prev y: " << cam._yaw << std::endl;
            std::cout << "prev p: " << cam._pitch << std::endl;
            std::cout << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << std::endl;
            cam._pos = worldPos;

            // Make sure we are accounting for the radius and everything
            cam._yaw = -glm::degrees(std::atan(cam._pos.x) * std::atan(cam._pos.z / cam._pos.y));
            // cam._pitch = glm::degrees(std::atan(glm::distance(cam._pos.x / -2.f, cam._pos.y / cam._pos.z / -2.f)));
            // constrainPitch(cam);
            cam.update();

            std::cout << "yaw: " << cam._yaw << std::endl;
            std::cout << "pitch: " << cam._pitch << std::endl;

            _view._engine.shiftPressed = true;
        } else if (!glfwGetKey(_view.getWindow()._window, GLFW_KEY_RIGHT_SHIFT) && _view._engine.shiftPressed) {
            _view._engine.shiftPressed = false;
        }

        if (cam.flags & CF_Moveable) {
            cam.move(_view.getWindow());
        }
    }

    if (onProcessInput) {
        onProcessInput();
    }
}
