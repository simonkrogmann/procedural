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
    ShaderProgram.cpp
    ShaderProgram.h
)

add_executable(procedural ${sources})

target_link_libraries(procedural ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

target_compile_options(procedural PRIVATE ${DEFAULT_COMPILE_FLAGS})
