//
// Created by James Pickering on 5/17/25.
//

#pragma once

struct Camera;
struct Cursor;
struct Entity;
struct Event;

auto cursorMoved(Entity& ent, Cursor& cur, const Camera& cam) -> void;
auto handleMouseMoved(Entity& ent, Cursor& cur, Event& ev) -> void;
auto handleMousePressed(Entity& ent, Cursor& cur, Event& ev) -> void;
auto handleMouseReleased(Entity& ent, Cursor& cur, Event& ev) -> void;