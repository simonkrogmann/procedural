set(sources
    main.cpp
    Window.cpp
    Window.h
    Config.cpp
    Config.h
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

    FileWatcher.cpp
    FileWatcher.h
    util.cpp
    util.h
    util_convert.cpp
    util_yaml.cpp
)

add_executable(procedural-viewer ${sources})

qt5_use_modules(procedural-viewer OpenGL)

target_compile_options(procedural-viewer PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_link_libraries(procedural-viewer ${GLFW_LIBRARIES} glbinding::glbinding)

add_custom_target(format-viewer
    COMMAND clang-format -i ${sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    COMMENT "Formatting code"
    VERBATIM)

add_dependencies(procedural-viewer format-viewer)
