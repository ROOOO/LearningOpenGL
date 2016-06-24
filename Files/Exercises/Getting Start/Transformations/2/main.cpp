//
//  main.cpp
//  EX_GS_T_2
//
//  Created by King on 16/6/24.
//  Copyright © 2016年 King. All rights reserved.
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CommonSettings.hpp"
#include "TextureReader.hpp"
#include "ShaderReader.hpp"

int main(int argc, const char * argv[]) {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("EX_GS_T_1");
  if (window == nullptr) {
    std::cout << "Create window failed" << std::endl;
    glfwTerminate();
    return -1;
  }
  
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
  };
  GLuint indices[] = {
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
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  
#ifdef __APPLE__
  string path = "/Transformations/2/";
#else
  string path = "\\Transformations\\2\\";
#endif
  
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_GS_T_2_Vertex.shader").c_str(), Settings.CCExercisesPath(path + "EX_GS_T_2_Fragment.shader").c_str());
  
  GLuint textures[2];
  TextureReader tex1(Settings.CCResourcesPath("container.jpg").c_str());
  textures[0] = tex1.getTexture();
  TextureReader tex2(Settings.CCResourcesPath("awesomeface.png").c_str());
  textures[1] = tex2.getTexture();
  
  const GLchar* names[] = {
    "tex1", "tex2",
  };
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(glGetUniformLocation(shader.GetProgram(), names[i]), i);
      
    }

    shader.Use();

    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    trans = glm::scale(trans, glm::vec3(sin(glfwGetTime()), sin(glfwGetTime()), 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "transform"), 1, GL_FALSE, glm::value_ptr(trans));
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    trans = glm::mat4();
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, glm::radians((float)glfwGetTime() * 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.GetProgram(), "transform"), 1, GL_FALSE, glm::value_ptr(trans));
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  return 0;
}
