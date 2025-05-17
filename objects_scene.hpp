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

struct ObjectsScene : Scene {
    ObjectsScene(View& view, Engine& engine);

    Engine& engine;
    Entity* blockEnt;
    Entity* camEnt;
};