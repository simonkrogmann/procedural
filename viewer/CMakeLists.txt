set(sources
    main.cpp
    Window.cpp
    Window.h
    Project.cpp
    Project.h
    Renderer.cpp
    Renderer.h
    ProceduralRenderer.cpp
    ProceduralRenderer.h

    Drawable.cpp
    Drawable.h
    ScreenAlignedQuad.cpp
    ScreenAlignedQuad.h
    Program.cpp
    Program.h
    Shader.cpp
    Shader.h
    Texture.cpp
    Texture.h
    Framebuffer.cpp
    Framebuffer.h
)

add_executable(procedural-viewer ${sources})

qt5_use_modules(procedural-viewer OpenGL)

target_compile_options(procedural-viewer PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_link_libraries(procedural-viewer ${GLFW_LIBRARIES} glbinding::glbinding utilpp::utilpp)

option(CLANG_FORMAT "Add clang formatting to the build step" ON)
if (CLANG_FORMAT)
    add_custom_target(format-viewer
        COMMAND clang-format -i ${sources}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Formatting code"
        VERBATIM)
    add_dependencies(procedural-viewer format-viewer)
endif()
