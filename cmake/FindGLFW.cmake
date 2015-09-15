find_path(GLFW_INCLUDE_DIRS GLFW/glfw3.h
    $ENV{PROGRAMFILES}/GLFW/include/
    $ENV{PROGRAMW6432}/GLFW/include/
)
find_library(GLFW_LIBRARIES
    NAMES glfw3 glfw
    PATHS
    $ENV{PROGRAMFILES}/GLFW/lib
    $ENV{PROGRAMW6432}/GLFW/lib
)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIRS)
mark_as_advanced(GLFW_FOUND GLFW_INCLUDE_DIRS GLFW_LIBRARIES)
