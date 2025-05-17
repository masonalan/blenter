//
// Created by James Pickering on 5/17/25.
//

#include "mouse.hpp"

#include "../../object.hpp"
#include "camera.hpp"
#include "cursor.hpp"
#include "entity.hpp"

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
                Face{glm::vec3{-0.5f, 0.f, 0.0f}, Axis::X},
                Face{glm::vec3{0.f, -0.5f, 0.0f}, Axis::Y},
            };

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

                for (auto& c : convertedFace) {
                    c.x /= c.w;
                    c.y /= c.w;
                    c.z /= c.w;
                }

                const auto cursorPos = cur.clipSpacePos;
                auto isMatch = false;
                // switch (face.axis) {
                // case Axis::Z:
                isMatch = containsPoint(convertedFace, cursorPos);
                //if (cursorPos.x > convertedFace.at(0).x && cursorPos.x < convertedFace.at(1).x) {}
                //     break;
                // default:
                //     break;
                // }

                //std::cout << convertedFace.at(0).x << ", " << convertedFace.at(0).y << ", " << convertedFace.at(0).z << std::endl;
                // std::cout << convertedFace.at(0).x << ", " << convertedFace.at(0).y << ", " << convertedFace.at(0).z << std::endl;

                //std::cout << cursorPos.x << ", " << cursorPos.y << std::endl;

                // switch (face.axis) {
                // default:
                //     isMatch = convertedFace.at(0).x < cursorPos.x && convertedFace.at(1).x > cursorPos.x &&
                //               convertedFace.at(0).y < cursorPos.y && convertedFace.at(2).y > cursorPos.y;
                //     break;
                // }
                if (isMatch) {
                    //cur.cursorType = CursorType::Pointer;
                    ent.edge = face.center;
                    ent.state |= Hovered;
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

    if (ent.state & Hovered) {
        Cursor::instance().cursorType = getStyleAttr<CursorType>(ent.style, Attr::CursorType, ent.state);
        std::cout << (int)Cursor::instance().cursorType << std::endl;
    }
}

auto handleMouseMoved(Entity& ent, Cursor& cur) -> void {
    if (ent.flags & FollowsMouse) {
        ent.transform.pos = {cur.screenSpacePos, -1};
        applyTransform(ent.model, ent.transform);
    }

    if (ent.state & Depressed && cur.pressed) {
        if (ent.onDrag) {
            ent.onDrag(ent);
        }
    }

    if (ent.flags & ResizeOnFaceDrag && cur.pressed && ent.edge != glm::vec3{}) {
        if (ent.edge.x != 0) {
            ent.transform.size.x += delta(cur.clipSpacePos, cur.lastClipSpacePos).x * 2;
        } else if (ent.edge.y != 0) {
            ent.transform.size.y += delta(cur.clipSpacePos, cur.lastClipSpacePos).x * 2;
        } else if (ent.edge.z != 0) {
            ent.transform.size.z += delta(cur.clipSpacePos, cur.lastClipSpacePos).x * 2;
        }
        applyTransform(ent.model, ent.transform);
    }
}

auto handleMousePressed(Entity& ent, Cursor& cur) -> void {
    if (ent.state & Hovered && ent.flags & Depressable) {
        ent.state |= Depressed;
    }
}

auto handleMouseReleased(Entity& ent, Cursor& cur) -> void {
    if (ent.state & Depressed) {
        ent.state &= ~Depressed;
        if (ent.flags & Selectable) {
            ent.state |= Selected;
            if (ent.onClick) {
                ent.onClick(ent);
            }
        }
    }
    if (ent.flags & RotatesOnDrag) {
        commitRotation(ent);
    }
}