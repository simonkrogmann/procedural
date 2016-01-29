set(target procedural-viewer)

set(sources
    main.cpp
    Window.cpp
    Project.cpp
    ProceduralRenderer.cpp
)

set(includes
    Window.h
    Project.h
    ProceduralRenderer.h
)

set(resources
    shader/screenalignedquad.vert
    shader/procedural.frag
    shader/default.frag
)

set(libraries
    ${GLFW_LIBRARIES}
    glbinding::glbinding
    utilgpu::cpp utilgpu::gl utilgpu::qt
    Qt5::OpenGL
)

create_executable(${target} "${sources}" "${includes}" "${libraries}")
generate_resource_header(procedural ${target} "${resources}")
