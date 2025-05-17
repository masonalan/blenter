//
// Created by James Pickering on 9/1/24.
//

#pragma once

struct Texture {
    static auto fromPng(const char* path, bool alpha = true, bool flip = true) -> unsigned int;
};
