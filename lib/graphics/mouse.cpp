//
// Created by James Pickering on 5/17/25.
//

#include "mouse.hpp"

#include "../../object.hpp"
#include "camera.hpp"
#include "cursor.hpp"
#include "entity.hpp"

#include <algorithm>

struct ConvFace {
    std::vector<glm::vec4> bounds;
    glm::vec3 center;
    float zMin;
};

auto cursorMoved(Entity& ent, Cursor& cur, const Camera& cam) -> void {
    if (ent.flags & Hoverable) {
        switch (ent.vao.mode) {
        case RenderMode::Mode3D: {
            if (ent.flags & Dragging || cur.pressed) {
                return;
            }
            ent.edge = glm::vec3{0.0f, 0.0f, 0.0f};
            ent.state &= ~Hovered;
            //cur.cursorType = CursorType::Hand;
            // auto lastConverted = glm::vec4{-100};

            const auto faces = std::vector{
                Face{glm::vec3{0.0f, 0.0f, 0.5f}, Axis::Z},
                Face{glm::vec3{0.0f, 0.0f, -0.5f}, Axis::Z},
                Face{glm::vec3{0.5f, 0.f, 0.0f}, Axis::X},
                Face{glm::vec3{-0.5f, 0.f, 0.0f}, Axis::X},
                Face{glm::vec3{0.f, -0.5f, 0.0f}, Axis::Y},
                Face{glm::vec3{0.f, 0.5f, 0.0f}, Axis::Y},
            };

            auto convFaces = std::vector<ConvFace>{};
            for (const auto& face : faces) {
                auto bounds = std::vector<glm::vec4>{};
                switch (face.axis) {
                case Axis::X:
                    bounds = std::vector{glm::vec4{face.center.x, face.center.y - 0.5f, face.center.z - 0.5f, 1.f},
                                         glm::vec4{face.center.x, face.center.y + 0.5f, face.center.z - 0.5f, 1.f},
                                         glm::vec4{face.center.x, face.center.y + 0.5f, face.center.z + 0.5f, 1.f},
                                         glm::vec4{face.center.x, face.center.y - 0.5f, face.center.z + 0.5f, 1.f}};
                    break;
                case Axis::Y:
                    bounds = std::vector{glm::vec4{face.center.x - 0.5f, face.center.y, face.center.z - 0.5f, 1.f},
                                         glm::vec4{face.center.x + 0.5f, face.center.y, face.center.z - 0.5f, 1.f},
                                         glm::vec4{face.center.x + 0.5f, face.center.y, face.center.z + 0.5f, 1.f},
                                         glm::vec4{face.center.x - 0.5f, face.center.y, face.center.z + 0.5f, 1.f}};
                    break;
                case Axis::Z:
                    bounds = std::vector{glm::vec4{face.center.x - 0.5f, face.center.y - 0.5f, face.center.z, 1.f},
                                         glm::vec4{face.center.x + 0.5f, face.center.y - 0.5f, face.center.z, 1.f},
                                         glm::vec4{face.center.x + 0.5f, face.center.y + 0.5f, face.center.z, 1.f},
                                         glm::vec4{face.center.x - 0.5f, face.center.y + 0.5f, face.center.z, 1.f}};
                    break;
                }

                auto convertedFace = std::vector{cam.projection() * cam.view() * ent.model * bounds.at(0),
                                                 cam.projection() * cam.view() * ent.model * bounds.at(1),
                                                 cam.projection() * cam.view() * ent.model * bounds.at(2),
                                                 cam.projection() * cam.view() * ent.model * bounds.at(3)};

                auto minZ = std::numeric_limits<float>::max();
                for (auto& c : convertedFace) {
                    c.x /= c.w;
                    c.y /= c.w;
                    c.z /= c.w;
                    if (c.z < minZ) {
                        minZ = c.z;
                    }
                }

                auto c = ConvFace{};
                c.bounds = convertedFace;
                c.center = face.center;
                c.zMin = minZ;

                convFaces.push_back(c);
            }

            std::ranges::sort(convFaces, [](const ConvFace& lhs, const ConvFace& rhs) {
                return lhs.zMin < rhs.zMin;
            });

            for (const auto& cface : convFaces) {
                const auto cursorPos = cur.clipSpacePos;
                auto isMatch = false;

                isMatch = containsPoint(cface.bounds, cursorPos);

                if (isMatch) {
                    //cur.cursorType = CursorType::Pointer;
                    ent.edge = cface.center;
                    ent.state |= Hovered;
                    break;
                    // _activeEdge = true;
                }
            }
            break;
        }
        case RenderMode::Mode2D: {
            const auto point = cur.screenSpacePos;
            const auto res = containsPoint(ent.transform.pos, ent.transform.size, point);
            if (res) {
                ent.state |= Hovered;
            } else {
                ent.state &= ~Hovered;
            }
            break;
        }
        }
    }
}

auto handleMouseMoved(Entity& ent, Cursor& cur, Event& ev) -> void {
    if (ent.flags & FollowsMouse) {
        ent.transform.pos = {cur.screenSpacePos, -0.5f};
        // ent.transform.pos.x += ent.transform.size.x / 2.f;
        // ent.transform.pos.y -= ent.transform.size.y / 2.f;
        applyTransform(ent.model, ent.transform);
    }

    if (ent.state & Depressed && cur.pressed) {
        if (ent.onDrag) {
            ent.onDrag(ent);
        }
        ev.accept();
    }

    if (ent.flags & ResizeOnFaceDrag && cur.pressed && ent.edge != glm::vec3{}) {
        if (ent.edge.x != 0) {
            ent.transform.size.x -= delta(cur.clipSpacePos, cur.lastClipSpacePos).x * 2;
        } else if (ent.edge.y != 0) {
            ent.transform.size.y -= delta(cur.clipSpacePos, cur.lastClipSpacePos).x * 2;
        } else if (ent.edge.z != 0) {
            ent.transform.size.z -= delta(cur.clipSpacePos, cur.lastClipSpacePos).x * 2;
        }
        applyTransform(ent.model, ent.transform);
        ev.accept();
    }

    if (ent.state & Hovered) {
        cur.cursorType = getStyleAttr<CursorType>(ent.style, Attr::CursorType, ent.state);
        ev.accept();
    }
}

auto handleMousePressed(Entity& ent, Cursor& cur, Event& ev) -> void {
    if (ent.state & Hovered && ent.flags & Depressable) {
        ent.state |= Depressed;
        cur.cursorType = getStyleAttr<CursorType>(ent.style, Attr::CursorType, ent.state);
        ev.accept();
    }
}

auto handleMouseReleased(Entity& ent, Cursor& cur, Event& ev) -> void {
    if (ent.state & Depressed) {
        ent.state &= ~Depressed;
        if (ent.flags & Selectable) {
            ent.state |= Selected;
            if (ent.onClick) {
                ent.onClick(ent);
            }
        }
        cur.cursorType = getStyleAttr<CursorType>(ent.style, Attr::CursorType, ent.state);
        ev.accept();
    }
}