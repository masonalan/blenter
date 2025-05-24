//
// Created by James Pickering on 3/18/25.
//

#include "editor_scene.hpp"

#include "engine.hpp"
#include "lib/graphics/color.hpp"
#include "lib/graphics/view.hpp"
#include "lib/graphics/window.hpp"
#include "texture.hpp"

EditorScene::EditorScene(View& view, Engine& engine) :
    Scene{view},
    _engine{engine} {
    // _blockEntity = addEntity<BlockEntity>();
    // _blockEntity->setBlock(_engine.getSelectedBlock());
    // _blockEntity->setPosition({0, 0, -2});
    // _engine.onSelectBlock = [this](auto) {
    //     _blockEntity->setBlock(_engine.getSelectedBlock());
    // };

    floorEntity = addEntity<Entity>();
    floorEntity->vao = genVao(RenderMode::Mode3D);
    setStyleAttr(floorEntity->style, Attr::FillColor, 0, glm::vec4{0.5f, 0.f, 0.f, 1.f});
    floorEntity->transform.pos = {0.f, -0.4f, -3.f};
    floorEntity->transform.size = {2.f, 0.01f, 2.f};
    applyTransform(floorEntity->model, floorEntity->transform);

    loc = addEntity<Entity>();
    loc->vao = genVao(RenderMode::Mode3D);
    loc->transform.size = {0.05f, 0.05f, 0.05f};
    applyTransform(loc->model, loc->transform);
    setStyleAttr(loc->style, Attr::FillColor, Normal, color::yellow);

    cam = Camera{ProjectionType::Perspective};
    cam.flags |= CF_Moveable | CF_CursorControlsLookAt;
    cam.setSize(view.getWindow().getSize());

    onProcessInput = [this] {
        const auto forward = getForward(cam);
        std::cout << forward.x << ", " << forward.y << ", " << forward.z << std::endl;
        loc->transform.pos = forward;
        applyTransform(loc->model, loc->transform);
    };
}

// auto EditorScene::update() -> void {
// }

// auto ObjectsScene::render() const -> void {
//     getView().getShader().use();
//     getView().getShader().setMat4("view", _camera.view());
//     getView().getShader().setMat4("proj", _camera.projection());
//
//     _blockEntity.render(getView().getShader(), _camera);
// }

// auto EditorScene::wheelScrolled(float distance) -> void {
//     cam.zoom(distance);
// }

// auto EditorScene::mousePressed() -> void {
//     auto i = 0;
//     // for (auto& thumbnail : thumbnails) {
//     //     if (thumbnail.containsCursor()) {
//     //         currObject = i;
//     //         xRay.setRotation(blockEntities[currObject].getRotation());
//     //         yRay.setRotation(blockEntities[currObject].getRotation());
//     //         zRay.setRotation(blockEntities[currObject].getRotation());
//     //         xRay.commitRotation();
//     //         yRay.commitRotation();
//     //         zRay.commitRotation();
//     //         return;
//     //     }
//     //     ++i;
//     // }
//
//     //_blockEntity.setCursorCoords(view().getCursor(), _camera);
//     // if (_blockEntity->containsCursor()) {
//     //     _blockEntity->setDragging(true);
//     //     Cursor::instance().setCursorAction(CursorType::Expand);
//     // } else {
//     //     Cursor::instance().setCursorAction(CursorType::Fist);
//     // }
//
//     const auto pos = toWorldSpace(Cursor::instance().clipSpacePos, cam);
//
//     const auto block = addEntity<Entity>();
//     setPosition(*block, pos);
//     //block->setBlock(_engine.getSelectedBlock());
//     applyBlock(*_engine.getSelectedBlock(), *block);
//     blockEntities.push_back(block);
//
//     // } else {
//     //     auto obj = BlockEntity{blockEntities[currObject]};
//     //     obj.setRotation({0, 0});
//     //     obj.setPosition({worldCursorCoord, -4.0f});
//     //     sceneObjs.push_back(obj);
//     // }
// }
//
// auto EditorScene::mouseReleased() -> void {
//     // _blockEntity->setDragging(false);
//     // _blockEntity->commitRotation();
//
//     // if (objectsButton.containsCursor()) {
//     //     isShowingObjects = true;
//     //     objectsButton.setSelected(true);
//     //     scenesButton.setSelected(false);
//     // }
//     // if (scenesButton.containsCursor()) {
//     //     isShowingObjects = false;
//     //     objectsButton.setSelected(false);
//     //     scenesButton.setSelected(true);
//     // }
// }
//
// auto EditorScene::mouseMoved(Event& event) -> void {
//     // auto& cursor = Cursor::instance();
//     // _blockEntity->setCursorCoords(cursor, _camera);
//     //
//     // if (cursor.isPressed()) {
//     //     const auto cursorPos = cursor.getScreenSpacePosition();
//     //     const auto t = glm::vec2{cursorPos.x - cursor.posWhenLastPressed().x, -(cursorPos.y - cursor.posWhenLastPressed().y)};
//     //     _blockEntity->setRotationDelta(t, cursor);
//     // }
// }

// auto EditorScene::windowResized(glm::ivec2 size) -> void {
//     cam.setSize(size);
// }

// auto EditorScene::processInput() -> void {
// }
