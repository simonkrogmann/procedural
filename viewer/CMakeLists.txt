set(target procedural-viewer)

set(sources
    main.cpp
    Project.cpp
    ProceduralRenderer.cpp
)

set(includes
    Project.h
    ProceduralRenderer.h
)

set(resources
    shader/screenalignedquad.vert
    shader/procedural.frag
    shader/default.frag
)

set(libraries
    glbinding::glbinding
    utilgpu::cpp utilgpu::gl utilgpu::qt utilgpu::window
)

create_executable(${project} ${target} "${sources}" "${includes}" "${libraries}")
generate_resource_header(${project} ${target} "${resources}")
