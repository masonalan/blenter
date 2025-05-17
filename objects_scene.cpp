//
// Created by James Pickering on 3/18/25.
//

#include "objects_scene.hpp"

#include "engine.hpp"
#include "lib/graphics/view.hpp"
#include "lib/graphics/window.hpp"

ObjectsScene::ObjectsScene(View& view, Engine& eng) :
    Scene{view},
    engine{eng} {
    cam = Camera{ProjectionType::Perspective};
    cam.setSize(view.getWindow().getSize());

    camEnt = addEntity<Entity>();
    camEnt->flags |= Hoverable | Depressable;
    camEnt->vao.mode = RenderMode::Mode2D;
    camEnt->transform.pos = {0, 0, -1};
    camEnt->transform.size = {view.getWindow().getSize(), 1};
    camEnt->onDrag = [this](auto) {
        const auto& cur = Cursor::instance();
        const auto rot = glm::vec2{cur.screenSpacePos.x - cur.clipSpaceMouseDownAt.x,
                                   -(cur.screenSpacePos.y - cur.clipSpaceMouseDownAt.y)};
        blockEnt->transform.rot = blockEnt->transform.crot + rot;
        applyTransform(blockEnt->model, blockEnt->transform);
    };

    setStyleAttr(camEnt->style, Attr::CursorType, Hovered, CursorType::Hand);
    applyTransform(camEnt->model, camEnt->transform);

    blockEnt = addEntity<Entity>();
    blockEnt->flags |= Hoverable | Depressable | ResizeOnFaceDrag;
    blockEnt->vao = genVao(RenderMode::Mode3D);
    blockEnt->transform.pos = glm::vec3{0, 0, -2};

    applyBlock(*engine.getSelectedBlock(), *blockEnt);
    applyTransform(blockEnt->model, blockEnt->transform);

    engine.onSelectBlock = [this](auto) {
        applyBlock(*engine.getSelectedBlock(), *blockEnt);
        applyTransform(blockEnt->model, blockEnt->transform);
    };
}
