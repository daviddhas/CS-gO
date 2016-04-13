#include "csgo.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

void opengl_init();

using namespace csgo;

int main(int argc, char *argv[])
{
    opengl_init();

    int size = 256;
    std::vector<Float> vec1(size, 2);
    std::vector<Float> vec2(size, 3);

    auto in1 = std::make_shared<ReadTexture<Float>>(vec1);
    auto in2 = std::make_shared<ReadTexture<Float>>(vec2);

    auto out = std::make_shared<WriteTexture<Float>>(size);

    Program p({ in1, in2 }, { out });

    p.set(out, (in1 + in2) + in1);

    p.finish();
    p.run();

    std::vector<Float> output = out->read();

    return 0;
}

void opengl_init()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    GLFWwindow *window = glfwCreateWindow(1024, 512, "hi", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum result = glewInit();
    if (result != GLEW_OK)
    {
        std::cerr << glewGetErrorString(result) << std::endl;
        exit(1);
    }
}