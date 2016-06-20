#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CommonSettings.hpp"
#include "ShaderReader.hpp"

int main() {
  CommonSettings Settings;
  
  GLFWwindow *window;
  window = Settings.CreateWindow(window, "A");
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    return -1;
  }
  
  ShaderReader shader("EX_GS_Tex_1_Vertex.shader", "EX_GS_Tex_1_Fragment.shader");
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();  
  return -1;
}