set(sources
	main.cpp
	Window.cpp
	Window.h
)

add_executable(glphotomagic ${sources})

target_link_libraries(glphotomagic ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

target_compile_options(glphotomagic PRIVATE ${DEFAULT_COMPILE_FLAGS})
