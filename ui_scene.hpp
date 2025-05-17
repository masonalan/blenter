//
// Created by James Pickering on 3/18/25.
//

#pragma once

#include "lib/graphics/camera.hpp"
#include "lib/graphics/scene.hpp"

#include <memory>

struct Engine;
struct CursorEntity;

struct UiScene : Scene {
    UiScene(View& view, Engine& engine);

    Entity* btnBlocks;
    Entity* btnScenes;
    Entity* entCursor;
    std::vector<Entity*> blockBtns;

    Engine& engine;
};