set(sources
    main.cpp
    Window.cpp
    Window.h
    Renderer.cpp
    Renderer.h
    PhotoRenderer.cpp
    PhotoRenderer.h
    Drawable.cpp
    Drawable.h
    ScreenAlignedQuad.cpp
    ScreenAlignedQuad.h
    ShaderProgram.cpp
    ShaderProgram.h
)

add_executable(glphotomagic ${sources})

target_link_libraries(glphotomagic ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

target_compile_options(glphotomagic PRIVATE ${DEFAULT_COMPILE_FLAGS})
