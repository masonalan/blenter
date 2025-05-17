#include <glad/glad.h>
#include <glfw/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "block.hpp"
#include "block_entity.hpp"

#include <glm/gtx/component_wise.hpp>

#include "cursor_entity.hpp"
#include "editor_scene.hpp"
#include "engine.hpp"
#include "lib/graphics/cursor.hpp"
#include "lib/graphics/light.hpp"
#include "lib/graphics/shader.hpp"
#include "lib/graphics/view.hpp"
#include "lib/graphics/window.hpp"
#include "object.hpp"
#include "objects_scene.hpp"
#include "shapes.hpp"
#include "ui_scene.hpp"

constexpr auto WIN_WIDTH = 900;
constexpr auto WIN_HEIGHT = 700;
constexpr auto VIEWPORT_SCALE = 2;

auto ndcCursorCoord = glm::vec2{};
auto worldCursorCoord = glm::vec2{};
auto cursorPos = glm::vec2{};

auto isShowingObjects = true;
auto lastPos = glm::vec2{};

auto setupOpenGl() {
    // ---------------------------------------------------------------------------------------------------------------
    // Initialize GLAD
    //
    // This must be done before any OpenGL functions are called. GLFW provides a function to get the address of OpenGL
    // function pointers, and GLAD then loads them all. This address is OS-specific.
    // ---------------------------------------------------------------------------------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // --------------------------------------------------------------------------------------------------------------
    // Setup viewport
    //
    // Let OpenGL know how we want to display data with respect to the window. My MBP w/ retina display has a 2:1
    // viewport to window ratio.
    // --------------------------------------------------------------------------------------------------------------
    glViewport(0, 0, WIN_WIDTH * VIEWPORT_SCALE, WIN_HEIGHT * VIEWPORT_SCALE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

auto main() -> int {
    auto window = Window{"Blenter", {WIN_WIDTH, WIN_HEIGHT}};
    setupOpenGl();
    VertexBuffer::init();

    auto engine = Engine{"/Users/jamespickering/Documents/dev/art/example/"};
    auto view = View{window, engine};
    //
    // cursor.setViewport({WIN_WIDTH * VIEWPORT_SCALE, WIN_HEIGHT * VIEWPORT_SCALE});

    Cursor::instance().viewportSize = {WIN_WIDTH * VIEWPORT_SCALE, WIN_HEIGHT * VIEWPORT_SCALE};

    view.emplaceScene<ObjectsScene>(engine);
    view.emplaceScene<EditorScene>(engine);
    view.setUiScene(std::make_unique<UiScene>(view, engine));

    // --------------------------------------------------------------------------------------------------------------
    // Setup all vertex buffers
    // --------------------------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------------------------
    // Set up shaders
    // --------------------------------------------------------------------------------------------------------------
    // const auto shader = Shader{
    //     "main_shader.vert",
    //     "main_shader.frag",
    //     ShaderComponent::DirectionalLight | ShaderComponent::PointLight | ShaderComponent::Flashlight};
    // const auto instancedShader = Shader{
    //     "instanced_shader.vert",
    //     "main_shader.frag",
    //     ShaderComponent::DirectionalLight | ShaderComponent::PointLight | ShaderComponent::Flashlight};
    // const auto lightSourceShader = Shader{"main_shader.vert", "light_shader.frag"};
    //
    // const auto container = Container{};
    // const auto texturedCube = TexturedCube{shader};
    // const auto lightSource = LightSource{};
    //
    // //camera.setAspectRatio(static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT));
    //
    // const auto light = Light{
    //     {0.2f, 0.2f, 0.2f},
    //     {0.5f, 0.5f, 0.5f},
    //     {1.0f, 1.0f, 1.0f},
    //     lightSource.pos()};
    //
    // const auto directionalLight = DirectionalLight{
    //     {-0.2f, -1.f, -0.3f},
    //     {0.2f, 0.2f, 0.2f},
    //     {0.5f, 0.5f, 0.5f},
    //     {1.0f, 1.0f, 1.0f}};
    //
    // const auto pointLight = PointLight{
    //     {0.f, 0.f, 0.f},
    //     {0.2f, 0.2f, 0.2f},
    //     {0.5f, 0.5f, 0.5f},
    //     {1.0f, 1.0f, 1.0f},
    //     Distance::D50};
    //
    // auto flashlight = Flashlight{
    //     {0.f, 0.f, 0.f},
    //     {0.f, 0.f, 0.f},
    //     {0.05f, 0.05f, 0.05f},
    //     {0.5f, 0.5f, 0.5f},
    //     {1.0f, 1.0f, 1.0f},
    //     glm::cos(glm::radians(12.5f)),
    //     glm::cos(glm::radians(17.5f))};
    //
    // shader.use();
    // directionalLight.applyToShader(shader);
    // pointLight.applyToShader(shader);
    // flashlight.applyToShader(shader);
    //
    // instancedShader.use();
    // directionalLight.applyToShader(instancedShader);
    // pointLight.applyToShader(instancedShader);
    // flashlight.applyToShader(instancedShader);

    // auto blocks = std::vector<Block>{};
    // const auto path = std::filesystem::path{"/Users/jamespickering/Documents/dev/art/example/"};
    // const auto itr = std::filesystem::directory_iterator{path};
    // for (const auto& file : itr) {
    //     if (file.is_directory()) {
    //         blocks.emplace_back(file.path());
    //     }
    // }

    //auto block = Block{"/Users/jamespickering/Documents/dev/art/example/small"};

    // auto blockEntities = std::vector<BlockEntity>{};
    // for (auto& block : blocks) {
    //     blockEntities.emplace_back(block);
    //     blockEntities.back().setPosition({0.0f, 0.0f, -2.0f});
    // }

    // auto cursorEntity = CursorEntity{cursor};
    // cursorEntity.setSize({0.07f, 0.07f});
    // auto xRay = Object{};
    // auto yRay = Object{};
    // auto zRay = Object{};

    auto currObject = 0;

    //object.setSize({0.1f, 0.5f, 0.1f});
    // xRay.setPosition({0.f, 0.0f, -2.0f});
    // yRay.setPosition({0.0f, 0.0f, -2.0f});
    // zRay.setPosition({0.0f, 0.0f, -2.0f});
    // const auto size = 0.006;
    // const auto len = 1;
    // xRay.setSize({size, size, len});
    // yRay.setSize({size, len, size});
    // zRay.setSize({len, size, size});
    // xRay.setFillColor({0.5f, 0.8f, 0.2f, 1.f});
    // yRay.setFillColor({0.8f, 0.5f, 0.2f, 1.f});
    // zRay.setFillColor({0.2f, 0.1f, 0.5f, 1.f});

    //auto thumbnails = std::vector<QuadEntity>{};
    auto offset = 0.f;
    // for (const auto& block : blocks) {
    //     auto quad = QuadEntity{cursor};
    //     quad.setTexture(block.getTextures().front());
    //     quad.setPos({-0.45f, 0.33f - offset});
    //     quad.setSize({0.1f, 0.1f});
    //     offset += 0.13f;
    //     thumbnails.emplace_back(quad);
    // }

    // auto objectsButton = QuadEntity{cursor};
    // objectsButton.setPos({-0.2f, -0.3f});
    // objectsButton.setSize({0.2f, 0.1f});
    // objectsButton.setTexture(Texture::fromPng("objects.png"));
    // objectsButton.setSelected(true);
    // auto scenesButton = QuadEntity{cursor};
    // scenesButton.setTexture(Texture::fromPng("scene.png"));
    // scenesButton.setPos({0.2f, -0.3f});
    // scenesButton.setSize({0.2f, 0.1f});

    // auto floor = Object{};
    // floor.fill = {0.5f, 0.f, 0.f, 1.f});
    // floor.setSize({2.f, 0.01f, 2.f});
    // floor.setPosition({0.f, -0.4f, -3.f});

    // auto sceneObjs = std::vector<Object>{};

    // cursor.setOnMouseDown([&blockEntities, &shader, &thumbnails, &currObject, &xRay, &yRay, &zRay, &sceneObjs]() {
    //     shader.setBool("mouseDown", true);
    //
    //     auto i = 0;
    //     for (auto& thumbnail : thumbnails) {
    //         if (thumbnail.containsCursor()) {
    //             currObject = i;
    //             xRay.setRotation(blockEntities[currObject].getRotation());
    //             yRay.setRotation(blockEntities[currObject].getRotation());
    //             zRay.setRotation(blockEntities[currObject].getRotation());
    //             xRay.commitRotation();
    //             yRay.commitRotation();
    //             zRay.commitRotation();
    //             return;
    //         }
    //         ++i;
    //     }
    //
    //     if (isShowingObjects) {
    //         blockEntities[currObject].setCursorCoords(cursor, camera);
    //
    //         if (blockEntities[currObject].containsCursor()) {
    //             blockEntities[currObject].setDragging(true);
    //             cursor.setCursorAction(CursorType::Expand);
    //         } else {
    //             cursor.setCursorAction(CursorType::Fist);
    //         }
    //
    //     } else {
    //         auto obj = BlockEntity{blockEntities[currObject]};
    //         obj.setRotation({0, 0});
    //         obj.setPosition({worldCursorCoord, -4.0f});
    //         sceneObjs.push_back(obj);
    //     }
    // });
    //
    // cursor.setOnMouseUp([&blockEntities, &shader, &currObject, &objectsButton, &scenesButton]() {
    //     blockEntities[currObject].setDragging(false);
    //     shader.setBool("mouseDown", false);
    //
    //     if (objectsButton.containsCursor()) {
    //         isShowingObjects = true;
    //         objectsButton.setSelected(true);
    //         scenesButton.setSelected(false);
    //     }
    //     if (scenesButton.containsCursor()) {
    //         isShowingObjects = false;
    //         objectsButton.setSelected(false);
    //         scenesButton.setSelected(true);
    //     }
    // });

    // ---------------------------------------------------------------------------------------------------------------
    // Render loop
    //
    // Check to see if GLFW has been instructed to close the window, and if so break. An iteration of a render loop is
    // called a frame. Thus, a frame rate is how many times the render loop is executed in some period.
    // ---------------------------------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window.getGlfwWindow())) {
        window.processInput();

        view.update();
        view.render();
        //
        // cursorEntity.update(worldCursorCoord, cursor.isPressed());
        // cursor.setCursorAction(CursorType::Hand);
        //
        // if (isShowingObjects) {
        //     if (cursor.isPressed()) {
        //         const auto t = glm::vec2{cursorPos.x - cursor.posWhenLastPressed().x, -(cursorPos.y - cursor.posWhenLastPressed().y)};
        //         blockEntities[currObject].setRotationDelta(t, cursor);
        //         if (!blockEntities[currObject].isDragging()) {
        //             xRay.setRotationDelta(t, cursor);
        //             yRay.setRotationDelta(t, cursor);
        //             zRay.setRotationDelta(t, cursor);
        //         }
        //         //isFirst = false;
        //
        //     } else {
        //         //isFirst = true;
        //         blockEntities[currObject].commitRotation();
        //         xRay.commitRotation();
        //         yRay.commitRotation();
        //         zRay.commitRotation();
        //     }
        //     blockEntities[currObject].setCursorCoords(cursor, camera);
        //
        //     blockEntities[currObject].render(shader, camera);
        //     xRay.render(shader, camera);
        //     yRay.render(shader, camera);
        //     zRay.render(shader, camera);
        //
        // } else {
        //     floor.setCursorCoords(cursor, camera);
        //     floor.render(shader, camera);
        //     for (const auto& obj : sceneObjs) {
        //         obj.render(shader, camera);
        //     }
        // }
        //
        // for (auto& t : thumbnails) {
        //     t.mouseEnter(worldCursorCoord);
        //     if (t.containsCursor()) {
        //         cursor.setCursorAction(CursorType::Pointer);
        //     }
        //     t.render(shader, camera);
        // }
        //
        // scenesButton.mouseEnter(worldCursorCoord);
        // objectsButton.mouseEnter(worldCursorCoord);
        // if (scenesButton.containsCursor()) {
        //     cursor.setCursorAction(CursorType::Pointer);
        // }
        // if (objectsButton.containsCursor()) {
        //     cursor.setCursorAction(CursorType::Pointer);
        // }
        //
        // scenesButton.render(shader, camera);
        // objectsButton.render(shader, camera);
        //
        // cursorEntity.render(shader, camera, -0.999);
        //
        // cursor.update();

        // -------------------------------------------------------------------------------------------------------
        // Swap the color buffer that is used to render to during this render and show it as output on the screen.
        // -------------------------------------------------------------------------------------------------------
        glfwSwapBuffers(window.getGlfwWindow());

        // -----------------------------------------------
        // Poll for any events, like keyboard/mouse events
        // -----------------------------------------------
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// auto framebufferSizeCallback(GLFWwindow*, int width, int height) -> void {
//     glViewport(0, 0, width, height);
// }
//
// auto isFirst = true;
//
// auto cursorCallback(GLFWwindow* window, const double xPos, const double yPos) -> void {
//     if (isFirst) {
//         lastPos.x = xPos;
//         lastPos.y = yPos;
//
//         isFirst = false;
//     }
//     const auto deltaX = xPos - lastPos.x;
//     const auto deltaY = yPos - lastPos.y;
//     cursorPos.x += deltaX;
//     cursorPos.y -= deltaY;
//     lastPos.x = xPos;
//     lastPos.y = yPos;
//
//     cursor.setScreenSpacePosition(cursorPos);
//
//     ndcCursorCoord = cursor.getClipSpacePosition();
//     ndcCursorCoord.x = std::fmin(1.f, std::fmax(-1.f, ndcCursorCoord.x));
//     ndcCursorCoord.y = std::fmin(1.f, std::fmax(-1.f, ndcCursorCoord.y));
//     worldCursorCoord = cursor.toWorldSpace(ndcCursorCoord, camera);
//
//     // if (deltaX != 0 || deltaY != 0) {
//     //     std::cout << cursor.getClipSpacePosition().x << ", " << cursor.getClipSpacePosition().y << std::endl;
//     // }
// }
//
// auto scrollCallback(GLFWwindow*, double, double yOffset) -> void {
//     camera.zoom(static_cast<float>(yOffset));
// }
//
// auto processInput(GLFWwindow* window) -> void {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//         glfwSetWindowShouldClose(window, true);
//     }
//
//     cursor.setPressed(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
//
//     if (!isShowingObjects) {
//         camera.move(window);
//     }
// }
