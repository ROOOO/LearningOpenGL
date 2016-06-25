//
//  main.cpp
//  EX_GS_CS_3
//
//  Created by King on 16/6/25.
//  Copyright © 2016年 King. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ShaderReader.hpp"
#include "CommonSettings.hpp"
#include "TextureReader.hpp"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, const char * argv[]) {
  CommonSettings Settings;
  
  GLFWwindow* window = Settings.CreateWindow();
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    glfwTerminate();
    return -1;
  }
  
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
  };
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#ifdef __APPLE__
  string path = "/Coordinate System/3/";
#else
  string path = "\\Coordinate System\\3\\";
#endif

  ShaderReader shader(Settings.CCExercisesPath(path + "EX_GS_CS_3_Vertex.shader").c_str(), Settings.CCExercisesPath(path + "EX_GS_CS_3_Fragment.shader").c_str());
  
  GLuint textures[2];
  TextureReader tex1(Settings.CCResourcesPath("container.jpg").c_str());
  TextureReader tex2(Settings.CCResourcesPath("awesomeface.png").c_str());
  textures[0] = tex1.getTexture();
  textures[1] = tex2.getTexture();
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
  glm::mat4 projMat;
  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);
  projMat = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
  
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };
  
  shader.Use();
  GLint modelLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projLoc = glGetUniformLocation(shader.GetProgram(), "projMat");

  glEnable(GL_DEPTH_TEST);
  
  const GLchar* names[] = {
    "tex1", "tex2",
  };
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (GLuint i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(glGetUniformLocation(shader.GetProgram(), names[i]), i);
    }
    
    shader.Use();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));

    for (GLuint i = 0; i < 10; i++) {
      if (i % 3 == 0) {
        modelMat = glm::mat4();
        modelMat = glm::translate(modelMat, cubePositions[i]);
        modelMat = glm::rotate(modelMat, glm::radians((float)glfwGetTime() * 45.0f), glm::vec3(0.5f, 1.0f, -0.5f));
      } else {
        modelMat = glm::mat4();
        modelMat = glm::translate(modelMat, cubePositions[i]);
      }
      
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glfwSwapBuffers(window);
  }
  
  glDeleteTextures(2, textures);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  
  return 0;
}
