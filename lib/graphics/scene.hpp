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

    auto update() -> void;
    auto render() const -> void;
    auto wheelScrolled(float offset) -> void;
    auto mousePressed() const -> void;
    auto mouseReleased() const -> void;
    auto mouseMoved(Event& event) const -> void;
    auto windowResized(glm::ivec2 size) -> void;
    auto processInput() -> void;
    //
    // [[nodiscard]] virtual auto getCamera() const -> Camera& = 0;

    [[nodiscard]] auto getView() -> View&;
    [[nodiscard]] auto getView() const -> const View&;

    template <typename T, typename... Args>
        requires std::is_base_of_v<Entity, T>
    auto addEntity(Args&&... args) -> T* {
        _entities.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast<T*>(_entities.back().get());
    }

    int flags = 0;

    View& _view;
    Camera cam;

private:
    std::vector<std::unique_ptr<Entity>> _entities;
};
