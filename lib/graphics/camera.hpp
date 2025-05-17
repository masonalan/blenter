//
// Created by James Pickering on 9/1/24.
//

#pragma once

#include <glm/glm.hpp>

#include <functional>

struct Window;

enum class ProjectionType {
    Perspective,
    Orthographic
};

struct Camera {
    Camera(ProjectionType type);

    auto setSize(glm::ivec2 size) -> void;
    auto setSpeed(float speed) noexcept -> void;

    [[nodiscard]] auto view() const noexcept -> glm::mat4;
    [[nodiscard]] auto projection() const noexcept -> glm::mat4;
    [[nodiscard]] auto invProjView() const noexcept -> glm::mat4;
    [[nodiscard]] auto position() const noexcept -> glm::vec3;
    [[nodiscard]] auto front() const noexcept -> glm::vec3;
    [[nodiscard]] auto getWorldPos(float z) const noexcept -> glm::vec3;

    auto lookAt(float x, float y) noexcept -> void;
    auto move(const Window& window) noexcept -> void;
    auto zoom(float amount) noexcept -> void;

    std::function<void(bool)> onMove;

protected:
    auto update() -> void;

private:
    ProjectionType _projectionType;
    glm::vec3 _pos{0.f, 0.f, 0.f};
    glm::vec3 _front{0.f, 0.f, -1.f};
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp{0, 1, 0};
    glm::ivec2 _size;

    glm::mat4 _proj;
    glm::mat4 _lookAt;

    float _deltafloatime = 0.f;
    float _lastFrame = 0.f;
    float _aspectRatio;
    float _fov{45};
    float _lastX;
    float _lastY;
    float _pitch;
    float _yaw{-90};

    bool _cursorMovedOnce{false};
    float _speed{10.f};

    static constexpr float MaxPitch{89};
    static constexpr float Near{0.1};
    static constexpr float Far{100.f};
};
