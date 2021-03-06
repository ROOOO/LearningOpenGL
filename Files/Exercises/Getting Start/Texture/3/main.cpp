#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#ifdef __APPLE__
#include "CommonSettings.hpp"
#else
#include "../../../../Getting Start/CommonSettings.hpp"
#endif
#include "ShaderReader.hpp"
#include <SOIL/SOIL.h>

int main() {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("EX_GS_Tex_3");
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    return -1;
  }
  
#ifdef __APPLE__
  string path = "/Texture/3/";
#else
  string path = "\\Texture\\3\\";
#endif
  
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_GS_Tex_3_Vertex.shader").c_str(), Settings.CCExercisesPath(path + "EX_GS_Tex_3_Fragment.shader").c_str());
  
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f, 0.55f, 0.55f,
    0.5f, -0.5f, 0.0f, 0.55f, 0.45f,
    -0.5f, -0.5f, 0.0f, 0.45f, 0.45f,
    -0.5f, 0.5f, 0.0f, 0.45f, 0.55f,
  };
  GLint indices[] = {
    0, 1, 2,
    0, 2, 3,
  };
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  
  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  
  GLuint texture;
  glGenTextures(1, &texture);
  
  unsigned char* image;
  int texWidth, texHeight;
  image = SOIL_load_image(Settings.CCResourcesPath("container.jpg").c_str(), &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
  
  glBindTexture(GL_TEXTURE_2D, texture);
    
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(texture);
    
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader.GetProgram(), "tex"), 0);

    shader.Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return -1;
}