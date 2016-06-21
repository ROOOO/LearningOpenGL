#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#ifdef __APPLE__
//#include "CommonSettings.hpp"
#else
#include "../../../../Getting Start/CommonSettings.hpp"
#endif
#include "ShaderReader.hpp"

int main() {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("A");
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    return -1;
  }
  
  ShaderReader shader((Settings.GetExercisesFolder() + "EX_GS_Tex_1\\EX_GS_Tex_1_Vertex.shader").c_str(), "EX_GS_Tex_1_Fragment.shader");
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();  
  return -1;
}
