set(sources
    main.cpp
    Window.cpp
    Window.h
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
    util.cpp
    util.h
    convert.cpp
    convert.h
)

add_executable(procedural ${sources})

qt5_use_modules(procedural OpenGL)

target_link_libraries(procedural ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

target_compile_options(procedural PRIVATE ${DEFAULT_COMPILE_FLAGS})
