add_executable(glphotomagic main.cpp)

target_link_libraries(glphotomagic ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

target_compile_options(glphotomagic PRIVATE ${DEFAULT_COMPILE_FLAGS})
