//
// Created by James Pickering on 5/17/25.
//

#pragma once

struct Camera;
struct Cursor;
struct Entity;

auto cursorMoved(Entity& ent, Cursor& cur, const Camera& cam) -> void;
auto handleMouseMoved(Entity& ent, Cursor& cur) -> void;
auto handleMousePressed(Entity& ent, Cursor& cur) -> void;
auto handleMouseReleased(Entity& ent, Cursor& cur) -> void;