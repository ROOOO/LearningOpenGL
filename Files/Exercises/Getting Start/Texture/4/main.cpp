#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CommonSettings.hpp"
#include "ShaderReader.hpp"

int main() {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("EX_GS_Tex_4");
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    return -1;
  }
  
#ifdef __APPLE__
  string path = "/Texture/4/";
#else
  string path = "\\Texture\\4\\";
#endif
  
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_GS_Tex_4_Vertex.shader").c_str(), Settings.CCExercisesPath(path + "EX_GS_Tex_4_Fragment.shader").c_str());
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return -1;
}