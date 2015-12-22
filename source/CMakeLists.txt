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
    Group.h
)

add_executable(procedural ${sources})

target_link_libraries(procedural ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

target_compile_options(procedural PRIVATE ${DEFAULT_COMPILE_FLAGS})
