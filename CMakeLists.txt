cmake_minimum_required(VERSION 3.27)
project(lighting)

set(CMAKE_CXX_STANDARD 23)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(lighting main.cpp
        lib/graphics/shader.cpp
        lib/graphics/shader.hpp
        shapes.cpp
        shapes.hpp
        texture.cpp
        texture.hpp
        lib/graphics/material.cpp
        lib/graphics/material.hpp
        lib/graphics/light.cpp
        lib/graphics/light.hpp
        object.hpp
        object.cpp
        lib/graphics/camera.hpp
        lib/graphics/camera.cpp
        cursor_entity.hpp
        cursor_entity.cpp
        lib/graphics/cursor.cpp
        lib/graphics/cursor.hpp
        lib/graphics/cursor_type.hpp
        block.hpp
        block_entity.cpp
        block_entity.hpp
        quad_entity.cpp
        quad_entity.hpp
        lib/graphics/view.cpp
        lib/graphics/view.hpp
        lib/graphics/window.hpp
        lib/graphics/window.cpp
        lib/graphics/scene.cpp
        lib/graphics/scene.hpp
        objects_scene.cpp
        objects_scene.hpp
        engine.cpp
        engine.hpp
        ui_scene.cpp
        ui_scene.hpp
        lib/graphics/entity.cpp
        lib/graphics/entity.hpp
        lib/graphics/event.cpp
        lib/graphics/event.hpp
        editor_scene.cpp
        editor_scene.hpp
        lib/graphics/style.cpp
        lib/graphics/style.hpp
        lib/graphics/mouse.cpp
        lib/graphics/mouse.hpp
        lib/graphics/color.hpp)

target_link_libraries(lighting PRIVATE glad::glad)
target_link_libraries(lighting PRIVATE glfw)
target_link_libraries(lighting PRIVATE glm::glm)

target_include_directories(lighting PRIVATE ${Stb_INCUDE_DIR})

add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/shaders/main_shader.frag
        ${PROJECT_BINARY_DIR}/main_shader.frag)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/shaders/light_shader.frag
        ${PROJECT_BINARY_DIR}/light_shader.frag)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/shaders/main_shader.vert
        ${PROJECT_BINARY_DIR}/main_shader.vert)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/shaders/instanced_shader.vert
        ${PROJECT_BINARY_DIR}/instanced_shader.vert)

add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/gradient-logo.png
        ${PROJECT_BINARY_DIR}/gradient-logo.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/large-logo.png
        ${PROJECT_BINARY_DIR}/large-logo.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/palette.png
        ${PROJECT_BINARY_DIR}/palette.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/nav-play-inverse.png
        ${PROJECT_BINARY_DIR}/nav-play-inverse.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/nav-play.png
        ${PROJECT_BINARY_DIR}/nav-play.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/logo.png
        ${PROJECT_BINARY_DIR}/logo.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/circle-logo.png
        ${PROJECT_BINARY_DIR}/circle-logo.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/btn-play.png
        ${PROJECT_BINARY_DIR}/btn-play.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/face.png
        ${PROJECT_BINARY_DIR}/face.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/face5.png
        ${PROJECT_BINARY_DIR}/face5.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/win-bg.png
        ${PROJECT_BINARY_DIR}/win-bg.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/cursor_pointer.png
        ${PROJECT_BINARY_DIR}/cursor_pointer.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/cursor_grabber.png
        ${PROJECT_BINARY_DIR}/cursor_grabber.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/cursor_resizer.png
        ${PROJECT_BINARY_DIR}/cursor_resizer.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/cursor_resize.png
        ${PROJECT_BINARY_DIR}/cursor_resize.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/cursor_hand.png
        ${PROJECT_BINARY_DIR}/cursor_hand.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/vase.png
        ${PROJECT_BINARY_DIR}/vase.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/scene.png
        ${PROJECT_BINARY_DIR}/scene.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/objects.png
        ${PROJECT_BINARY_DIR}/objects.png)
add_custom_command(
        TARGET lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/resources/crosshair.png
        ${PROJECT_BINARY_DIR}/crosshair.png)