//
// Created by James Pickering on 3/18/25.
//

#include "ui_scene.hpp"

#include "lib/graphics/view.hpp"

#include "block.hpp"
#include "cursor_entity.hpp"
#include "engine.hpp"
#include "lib/graphics/window.hpp"
#include "quad_entity.hpp"
#include "texture.hpp"

UiScene::UiScene(View& view, Engine& eng) :
    Scene{view},
    engine{eng} {
    cam = Camera{ProjectionType::Orthographic};
    cam.setSize(view.getWindow().getSize());

    btnBlocks = addEntity<Entity>();
    btnBlocks->flags |= Hoverable | Selectable | Depressable;
    btnBlocks->vao = genVao(RenderMode::Mode2D);
    btnBlocks->transform.pos = {-160, -250, -2};
    btnBlocks->transform.size = {150, 80, 1};
    btnBlocks->textures.push_back(Texture::fromPng("objects.png"));
    btnBlocks->state = Selected;
    btnBlocks->onClick = [this](auto&) {
        btnScenes->state &= ~Selected;
        _view._currentScene = 0;
        entCursor->flags &= ~Invisible;
    };

    applyStyle(btnBlocks->style, StyleClass::Default);
    applyTransform(btnBlocks->model, btnBlocks->transform);

    btnScenes = addEntity<Entity>();
    btnScenes->flags |= Hoverable | Selectable | Depressable;
    btnScenes->vao = genVao(RenderMode::Mode2D);
    btnScenes->transform.pos = {160, -250, -2};
    btnScenes->transform.size = {150, 80, 1};
    btnScenes->textures.push_back(Texture::fromPng("scene.png"));
    btnScenes->onClick = [this](auto&) {
        btnBlocks->state &= ~Selected;
        _view._currentScene = 1;
        entCursor->flags |= Invisible;
    };

    applyStyle(btnScenes->style, StyleClass::Default);
    applyTransform(btnScenes->model, btnScenes->transform);

    auto offset = 0;
    auto i = 0;
    for (const auto& block : engine.getBlocks()) {
        auto blockEntity = addEntity<Entity>();
        blockEntity->flags |= Hoverable | Selectable | Depressable;
        blockEntity->vao = genVao(RenderMode::Mode2D);
        blockEntity->textures.push_back(block->getTextures().front());
        blockEntity->transform.pos = {-350, 270 - offset, -2};
        blockEntity->transform.size = {50, 50, 10};
        blockEntity->onClick = [this, idx = i++](auto& sender) {
            for (const auto& b : blockBtns) {
                if (b == &sender) {
                    continue;
                }
                b->state &= ~Selected;
            }
            engine.selectBlock(idx);
        };

        applyStyle(blockEntity->style, StyleClass::Default);
        applyTransform(blockEntity->model, blockEntity->transform);

        blockBtns.push_back(blockEntity);
        offset += 80;
    }

    auto type = CursorType::Pointer;
    while (type != CursorType::None) {
        curTexs[type] = Texture::fromPng(getImagePath(type));
        type = (CursorType)((int)type + 1);
    }

    entCursor = addEntity<Entity>();
    entCursor->vao = genVao(RenderMode::Mode2D);
    entCursor->textures.push_back(curTexs[CursorType::Pointer]);
    entCursor->flags |= FollowsMouse;
    entCursor->transform.pos.z = 0;
    entCursor->transform.pos.x = 0;
    entCursor->transform.size = {50, 50, 1};
    applyTransform(entCursor->model, entCursor->transform);

    crosshair = addEntity<Entity>();
    crosshair->vao = genVao(RenderMode::Mode2D);
    crosshair->textures.push_back(Texture::fromPng("crosshair.png"));
    crosshair->transform.pos = {0, 0, -2};
    crosshair->transform.size = {20, 20, 1};
    applyTransform(crosshair->model, crosshair->transform);

    onTick = [this] {
        const auto& cur = Cursor::instance();
        if (entCursor->textures.front() != curTexs.at(cur.cursorType)) {
            entCursor->textures.clear();
            entCursor->textures.push_back(curTexs.at(cur.cursorType));
        }
    };

    //Cursor::instance().cursorType = CursorType::Hand;
}
// Another reason grouping files by functionality rather than object is because we think about oh what do we want to
// work on, something that does something not something that is something. it is faster to find stuff this way.
