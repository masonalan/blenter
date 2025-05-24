//
// Created by James Pickering on 3/18/25.
//

#pragma once

#include "camera.hpp"
#include "entity.hpp"
#include "event.hpp"

#include <glm/vec2.hpp>

#include <memory>
#include <vector>

struct View;

enum SceneFlags {
    CameraZoomsOnScroll = 1 << 0,
};

struct Scene {
    explicit Scene(View& view);
    virtual ~Scene();

    auto render() const -> void;
    auto wheelScrolled(float offset) -> void;
    auto mousePressed(Event& ev) const -> void;
    auto mouseReleased(Event& ev) const -> void;
    auto mouseMoved(Event& ev) -> void;
    auto windowResized(glm::ivec2 size) -> void;
    auto processInput() -> void;

    [[nodiscard]] auto getView() -> View&;
    [[nodiscard]] auto getView() const -> const View&;

    template <typename T, typename... Args>
        requires std::is_base_of_v<Entity, T>
    auto addEntity(Args&&... args) -> T* {
        ents.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast<T*>(ents.back().get());
    }

    int flags = 0;
    View& _view;
    Camera cam;

    std::function<void()> onTick;
    std::function<void()> onDrag;
    std::function<void()> onMousePressed;
    std::function<void()> onMouseReleased;
    std::function<void()> onMouseMoved;
    std::function<void()> onProcessInput;

private:
    std::vector<std::unique_ptr<Entity>> ents;
};
