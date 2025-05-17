//
// Created by James Pickering on 3/18/25.
//

#include "engine.hpp"

#include "block.hpp"

Engine::Engine(std::filesystem::path path) :
    _path{std::move(path)},
    _selectedBlock{0} {
    for (const auto itr = std::filesystem::directory_iterator{_path}; const auto& file : itr) {
        if (file.is_directory()) {
            _blocks.push_back(std::make_unique<Block>(file.path()));
        }
    }
}

auto Engine::selectBlock(unsigned int idx) -> void {
    _selectedBlock = idx;
    if (onSelectBlock) {
        onSelectBlock(_selectedBlock);
    }
}

auto Engine::getBlocks() -> std::vector<std::unique_ptr<Block>>& {
    return _blocks;
}

auto Engine::getSelectedBlock() -> Block* {
    if (_selectedBlock >= _blocks.size()) {
        throw std::runtime_error("Selected block out of range");
    }
    return _blocks.at(_selectedBlock).get();
}
