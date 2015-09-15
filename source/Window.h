#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window();
    ~Window();

    int init(std::string title);
    void loop();
private:
    GLFWwindow * m_window;
};