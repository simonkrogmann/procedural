set(sources
    main.cpp
    Window.cpp
    Window.h
    Config.cpp
    Config.h
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
)

add_executable(procedural ${sources})

qt5_use_modules(procedural OpenGL)

target_compile_options(procedural PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_link_libraries(procedural ${GLFW_LIBRARIES} glbinding::glbinding)
