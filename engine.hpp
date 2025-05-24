//
// Created by James Pickering on 3/18/25.
//

#pragma once

#include "object.hpp"

#include <filesystem>
#include <functional>

struct Block;

struct Engine {
    explicit Engine(std::filesystem::path path);

    auto selectBlock(unsigned int idx) -> void;

    [[nodiscard]] auto getBlocks() -> std::vector<std::unique_ptr<Block>>&;
    [[nodiscard]] auto getSelectedBlock() -> Block*;

    bool shiftPressed = false;
    Axis selAxis = Axis::None;
    Axis lastAxis = Axis::None;

private:
    std::filesystem::path _path;
    std::vector<std::unique_ptr<Block>> _blocks;
    unsigned int _selectedBlock;


public:
    std::function<void(unsigned int)> onSelectBlock;
};
