set(sources
    main.cpp
    Window.cpp
    Window.h
    Project.cpp
    Project.h
    ProceduralRenderer.cpp
    ProceduralRenderer.h
)

set(target procedural-viewer)

add_executable(${target} ${sources})

target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

target_link_libraries(${target}
    ${GLFW_LIBRARIES}
    glbinding::glbinding
    utilgpu::cpp utilgpu::gl utilgpu::qt
    Qt5::OpenGL
)

option(CLANG_FORMAT "Add clang formatting to the build step" ON)
if (CLANG_FORMAT)
    add_custom_target(format-${target}
        COMMAND clang-format -i ${sources}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMENT "Formatting code"
        VERBATIM)
    add_dependencies(${target} format-${target})
endif()
