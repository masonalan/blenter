//
// Created by James Pickering on 3/18/25.
//

#pragma once

#include "block_entity.hpp"
#include "lib/graphics/camera.hpp"
#include "lib/graphics/scene.hpp"
#include "object.hpp"

struct Engine;
struct View;

struct EditorScene : Scene {
    EditorScene(View& view, Engine& engine);

    // auto update() -> void override;
    // // auto render() const -> void override;
    // auto wheelScrolled(float distance) -> void override;
    // // auto mousePressed() -> void override;
    // // auto mouseReleased() -> void override;
    // // auto mouseMoved(Event& event) -> void override;
    // auto windowResized(glm::ivec2 size) -> void override;
    // auto processInput() -> void override;

    std::vector<Entity*> blockEntities;
    Entity* floorEntity;

private:
    Engine& _engine;

    // BlockEntity* _blockEntity;
};