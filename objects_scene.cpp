//
// Created by James Pickering on 3/18/25.
//

#include "objects_scene.hpp"

#include "engine.hpp"
#include "lib/graphics/color.hpp"
#include "lib/graphics/view.hpp"
#include "lib/graphics/window.hpp"

#include <glm/ext/scalar_constants.hpp>

constexpr float factor = 0.3;

ObjectsScene::ObjectsScene(View& view, Engine& eng) :
    Scene{view},
    engine{eng} {
    cam = Camera{ProjectionType::Perspective};
    cam.setSize(view.getWindow().getSize());
    cam._yaw = 0;
    cam.update();

    const auto sinYaw = std::sin(glm::radians(-cam._yaw));
    const auto cosYaw = std::cos(glm::radians(-cam._yaw));
    const auto sinPitch = std::sin(glm::radians(cam._pitch));
    const auto cosPitch = std::cos(glm::radians(cam._pitch));

    cam._pos.x = -2 * cosYaw * cosPitch;
    cam._pos.y = -2 * sinPitch;
    cam._pos.z = 2 * sinYaw * cosPitch;

    auto cs = glm::vec4{-1, 0, 0.0, 1};
    auto transform = Transform{};
    transform.pos = cam._pos;
    auto ws = glm::inverse(cam.projection() * cam.view()) * cs;
    std::cout << "CS:    " << cs.x << ", " << cs.y << ", " << cs.z << std::endl;
    std::cout << "START: " << ws.x << ", " << ws.y << ", " << ws.z << std::endl;

    // cam._pos.z = -2;

    //cam._yaw += delta.x;
    // cam._yaw = 45;
    // cam._pitch = 45;
    // constrainPitch(cam);
    // cam.update();
    //
    // const auto sinYaw = std::sin(glm::radians(-cam._yaw));
    // const auto cosYaw = std::cos(glm::radians(-cam._yaw));
    // const auto sinPitch = std::sin(glm::radians(cam._pitch));
    // const auto cosPitch = std::cos(glm::radians(cam._pitch));
    //
    // cam._pos.x = -2 * cosYaw * cosPitch;
    // cam._pos.y = -2 * sinPitch;
    // cam._pos.z = 2 * sinYaw * cosPitch;
    // cam._yaw = -8=90;
    // std::cout << "test: " << std::cos(glm::radians(cam._yaw)) << std::endl;
    // std::cout << "test: " << std::sin(glm::radians(cam._yaw)) << std::endl;
    //cam._pos = glm::vec3{0, 0, -2};
    // cam._pos.x = -std::cos(glm::radians(cam._yaw)) * 2;
    // cam._pos.z = -std::sin(glm::radians(cam._yaw)) * 2;
    // cam.update();

    // camEnt = addEntity<Entity>();
    // camEnt->flags |= Hoverable | Depressable;
    // //camEnt->vao = genVao(RenderMode::Mode3D);
    //
    // camEnt->vao.mode = RenderMode::Mode3D;
    // camEnt->transform.pos = {0, 0, -3};
    // camEnt->transform.size = {view.getWindow().getSize(), 1};

    // setStyleAttr(camEnt->style, Attr::CursorType, Hovered, CursorType::Hand);
    // setStyleAttr(camEnt->style, Attr::CursorType, Depressed, CursorType::Fist);
    // applyTransform(camEnt->model, camEnt->transform);

    const auto width = 0.003f;
    const auto len = 2.f;
    zAxis = addEntity<Entity>();
    zAxis->vao = genVao(RenderMode::Mode3D);
    zAxis->transform.size.x = width;
    zAxis->transform.size.y = width;
    zAxis->transform.size.z = len;
    applyTransform(zAxis->model, zAxis->transform);
    setStyleAttr(zAxis->style, Attr::FillColor, Normal, color::green);

    yAxis = addEntity<Entity>();
    yAxis->vao = genVao(RenderMode::Mode3D);
    yAxis->transform.size.x = width;
    yAxis->transform.size.y = len;
    yAxis->transform.size.z = width;
    applyTransform(yAxis->model, yAxis->transform);
    setStyleAttr(yAxis->style, Attr::FillColor, Normal, color::turquoise);

    xAxis = addEntity<Entity>();
    xAxis->vao = genVao(RenderMode::Mode3D);
    xAxis->transform.size.x = len;
    xAxis->transform.size.y = width;
    xAxis->transform.size.z = width;
    applyTransform(xAxis->model, xAxis->transform);
    setStyleAttr(xAxis->style, Attr::FillColor, Normal, color::green);

    blockEnt = addEntity<Entity>();
    blockEnt->flags |= Hoverable | Depressable | ResizeOnFaceDrag;
    blockEnt->vao = genVao(RenderMode::Mode3D);
    blockEnt->transform.pos = glm::vec3{0, 0, 0};
    applyBlock(*engine.getSelectedBlock(), *blockEnt);
    applyTransform(blockEnt->model, blockEnt->transform);
    setStyleAttr(blockEnt->style, Attr::CursorType, Hovered, CursorType::Expand);
    setStyleAttr(blockEnt->style, Attr::CursorType, Depressed, CursorType::Fist);

    xzPlane = addEntity<Entity>();
    xzPlane->flags |= ShowGrid;
    xzPlane->vao = genVao(RenderMode::Mode3D);
    xzPlane->transform.size.x = len;
    xzPlane->transform.size.y = 0.001;
    xzPlane->transform.size.z = len;
    applyTransform(xzPlane->model, xzPlane->transform);
    setStyleAttr(xzPlane->style, Attr::FillColor, Normal, color::grey);

    rayEnt = addEntity<Entity>();
    rayEnt->vao = genVao(RenderMode::Mode3D);
    rayEnt->transform.size.x = width;
    rayEnt->transform.size.y = len;
    rayEnt->transform.size.z = width;
    applyTransform(rayEnt->model, rayEnt->transform);
    setStyleAttr(rayEnt->style, Attr::FillColor, Normal, glm::vec4(0, 1, 0, 1));

    rayBlockEnt = addEntity<Entity>();
    rayBlockEnt->vao = genVao(RenderMode::Mode3D);
    rayBlockEnt->transform.pos = glm::vec3{-1, 0, 0};
    rayBlockEnt->transform.size = glm::vec3{0.02, 0.02, 0.02};
    applyTransform(rayBlockEnt->model, rayBlockEnt->transform);
    setStyleAttr(rayBlockEnt->style, Attr::FillColor, Normal, color::orange);

    locOnPlane = addEntity<Entity>();
    locOnPlane->vao = genVao(RenderMode::Mode3D);
    locOnPlane->transform.size = glm::vec3{0.05, 0.005, 0.02};
    locOnPlane->transform.pos = glm::vec3{0, 0, -1};
    applyTransform(locOnPlane->model, locOnPlane->transform);
    setStyleAttr(locOnPlane->style, Attr::FillColor, Normal, color::yellow);

    onDrag = [this] {
        const auto& cur = Cursor::instance();
        const auto delta = glm::vec2{cur.screenSpacePos - cur.screenSpaceLastPos};

        cam._yaw += delta.x;
        cam._pitch += delta.y;
        constrainPitch(cam);
        cam.update();

        const auto sinYaw = std::sin(glm::radians(-cam._yaw));
        const auto cosYaw = std::cos(glm::radians(-cam._yaw));
        const auto sinPitch = std::sin(glm::radians(cam._pitch));
        const auto cosPitch = std::cos(glm::radians(cam._pitch));

        cam._pos.x = -2 * cosYaw * cosPitch;
        cam._pos.y = -2 * sinPitch;
        cam._pos.z = 2 * sinYaw * cosPitch;

        //std::cout << "pos: " << cam._pos.x << ", " << cam._pos.y << ", " << cam._pos.z << std::endl;
    };

    onTick = [this] {
        auto cs = Cursor::instance().clipSpacePos;
        // cs.x = cs.x / 2.f + 0.5f;
        // cs.y = cs.y / 2.f + 0.5f;
        //
        // std::cout << "cs:" << cs.x << "," << cs.y << std::endl;

        auto worldLoc = toWorldSpace({cs.x, cs.y}, cam, 0.807);// 0.1;
        //auto worldLoc = toWorldSpace({cs.x * 10.f * 2.f, cs.y * 10.f * 2.f}, cam, -7.f);// 0.1;

        //std::cout << "world loc: " << worldLoc.x << ", " << worldLoc.y << ", " << worldLoc.z << std::endl;
        //worldLoc.x = -0.9f;
        // rayBlockEnt->transform.pos = worldLoc;
        // applyTransform(rayBlockEnt->model, rayBlockEnt->transform);
        locOnPlane->transform.pos.x = worldLoc.x;
        locOnPlane->transform.pos.z = worldLoc.z;
        //locOnPlane->transform.rot.y = glm::degrees(sin(worldLoc.z) * sin(worldLoc.x));
        applyTransform(locOnPlane->model, locOnPlane->transform);
        //
        //std::cout << "worldLoc: " << worldLoc.x << " " << worldLoc.y << " " << worldLoc.z << std::endl;
    };

    onMousePressed = [this] {
        // std::cout << "SEL AXIS: " << (int)engine.selAxis << std::endl;
        // std::cout << "PRE: " << blockEnt->edge.x << ", " << blockEnt->edge.y << ", " << blockEnt->edge.z << std::endl;
        if (blockEnt->edge == glm::vec3{}) {
            return;
        }
        if (!blockEnt->edge.x) {
            auto color = getStyleAttr<glm::vec4>(xAxis->style, Attr::FillColor, Normal);
            color *= factor;
            setStyleAttr(xAxis->style, Attr::FillColor, Normal, color);
            color = getStyleAttr<glm::vec4>(xAxis->style, Attr::FillColor, Normal);
            std::cout << color.a << std::endl;
        }
        if (!blockEnt->edge.y) {
            auto color = getStyleAttr<glm::vec4>(yAxis->style, Attr::FillColor, Normal);
            color *= factor;
            setStyleAttr(yAxis->style, Attr::FillColor, Normal, color);
        }
        if (!blockEnt->edge.z) {
            auto color = getStyleAttr<glm::vec4>(zAxis->style, Attr::FillColor, Normal);
            color *= factor;
            setStyleAttr(zAxis->style, Attr::FillColor, Normal, color);
        }
    };

    onMouseReleased = [this] {
        if (blockEnt->edge == glm::vec3{}) {
            return;
        }
        if (!blockEnt->edge.x) {
            auto color = getStyleAttr<glm::vec4>(xAxis->style, Attr::FillColor, Normal);
            color /= factor;
            setStyleAttr(xAxis->style, Attr::FillColor, Normal, color);
        }
        if (!blockEnt->edge.y) {
            auto color = getStyleAttr<glm::vec4>(yAxis->style, Attr::FillColor, Normal);
            color /= factor;
            setStyleAttr(yAxis->style, Attr::FillColor, Normal, color);
        }
        if (!blockEnt->edge.z) {
            auto color = getStyleAttr<glm::vec4>(zAxis->style, Attr::FillColor, Normal);
            color /= factor;
            setStyleAttr(zAxis->style, Attr::FillColor, Normal, color);
        }
    };

    onMouseMoved = [this] {
        // std::cout << "Screen pos: " << Cursor::instance().screenSpacePos.x << ", " << Cursor::instance().screenSpacePos.y << std::endl;
        // std::cout << "NDC pos: " << Cursor::instance().clipSpacePos.x << ", " << Cursor::instance().clipSpacePos.y << std::endl;
        // std::cout << "edge: " << blockEnt->edge.x << ", " << blockEnt->edge.y << ", " << blockEnt->edge.z << std::endl;
        // std::cout << (int)engine.selAxis << std::endl;
        if (engine.selAxis != Axis::None) {
            engine.lastAxis = engine.selAxis;
        }
        if (blockEnt->edge.x != 0) {
            engine.selAxis = Axis::X;
        }
        if (blockEnt->edge.y != 0) {
            engine.selAxis = Axis::Y;
        }
        if (blockEnt->edge.z != 0) {
            engine.selAxis = Axis::Z;
        } else {
            engine.selAxis = Axis::None;
        }

        //rayEnt->transform.size.y = distance(glm::vec3{0}, rayBlockEnt->transform.pos);
        //std::cout << rayEnt->transform.size.y << std::endl;
        //rayEnt->transform.pos = rayBlockEnt->transform.pos / 2.f;
        rayEnt->transform.rot.y = 45.f;
        rayEnt->transform.rot.z = 90.f;
        rayEnt->transform.pos.z = 5.f;

        //rayEnt->transform.rot.y = glm::degrees(glm::acos(rayEnt->transform.pos.x) * glm::acos(rayEnt->transform.pos.z));
        //rayEnt->transform.rot.x = glm::degrees(glm::asin(rayEnt->transform.pos.y)) * 32 / 2;
        //rayEnt->transform.rot.z = glm::degrees(tan(rayBlockEnt->transform.pos.x / rayBlockEnt->transform.pos.y));
        ////////rayEnt->transform.rot.z = 90.f + glm::degrees(atan(rayBlockEnt->transform.pos.y / (rayBlockEnt->transform.pos.z * -rayBlockEnt->transform.pos.x)));
        //rayEnt->transform.rot.x = glm::degrees(atan(rayBlockEnt->transform.pos.y / (rayBlockEnt->transform.pos.z * rayBlockEnt->transform.pos.x)));
        //rayEnt->transform.rot.x = 0.f;
        //rayEnt->transform.rot.z = 45;
        ///////rayEnt->transform.rot.y = -glm::degrees(atan(rayBlockEnt->transform.pos.z / rayBlockEnt->transform.pos.x));
        // std::cout << "z (deg): " << glm::degrees(atan(rayBlockEnt->transform.pos.y / rayBlockEnt->transform.pos.x)) << std::endl;
        // std::cout << "x (deg): " << rayEnt->transform.rot.x << std::endl;
        //rayEnt->transform.rot.z = 90.f;
        //rayEnt->transform.rot.y = glm::degrees(acos(rayEnt->transform.pos.x) * asin(rayEnt->transform.pos.z));
        //std::cout << "x (pos): " << rayBlockEnt->transform.pos.x << "\tz (pos): " << rayEnt->transform.pos.z << std::endl;
        // std::cout << "x (deg): " << glm::degrees(asin(rayEnt->transform.pos.x)) << "\tz (deg): " << glm::degrees(asin(rayEnt->transform.pos.z)) << std::endl;

        //std::cout << rayEnt->transform.rot.y << std::endl;
        //rayEnt->transform.rot = {45.f, 0.f};
        applyTransform(rayEnt->model, rayEnt->transform);
        // std::cout << (int)engine.selAxis << std::endl;
    };

    engine.onSelectBlock = [this](auto) {
        applyBlock(*engine.getSelectedBlock(), *blockEnt);
        applyTransform(blockEnt->model, blockEnt->transform);
    };
}
