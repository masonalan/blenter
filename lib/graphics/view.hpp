//
// Created by James Pickering on 3/17/25.
//

#pragma once

#include "../../cursor_entity.hpp"
#include "camera.hpp"
#include "cursor.hpp"
#include "shader.hpp"

#include <vector>

struct Engine;
struct Scene;

struct View {
    explicit View(Window& window, Engine& engine);
    ~View();

    void update(const Cursor& cursor);
    auto update() -> void;
    auto render() const -> void;

    [[nodiscard]] auto getBlockEntities() -> std::vector<std::unique_ptr<Entity>>&;
    [[nodiscard]] auto getShader() const -> const Shader&;
    [[nodiscard]] auto getWindow() const -> const Window&;
    [[nodiscard]] auto getCurrentScene() const -> Scene*;

    auto setUiScene(std::unique_ptr<Scene> scene) -> void;

    template <typename T, typename... Args>
        requires std::is_base_of_v<Scene, T>
    auto emplaceScene(Args&&... args) -> Scene* {
        _scenes.push_back(std::make_unique<T>(*this, std::forward<Args>(args)...));
        return _scenes.back().get();
    }

    unsigned int _currentScene{0};

private:
    Window& _window;
    // Camera _cam2d;
    Shader _shader;

    std::vector<std::unique_ptr<Entity>> _blockEntities;
    std::vector<std::unique_ptr<Scene>> _scenes;
    std::unique_ptr<Scene> _uiScene;
};
