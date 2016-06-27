//
//  main.cpp
//  EX_GS_C_1
//
//  Created by King on 16/6/27.
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
#ifdef __APPLE__
#include "CommonSettings.hpp"
#else
#include "../../../../Getting Start/CommonSettings.hpp"
#endif
#include "TextureReader.hpp"
#include "ShaderReader.hpp"
#include "Camera.hpp"

GLboolean keys[1024];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (action == GLFW_PRESS) {
    keys[key] = true;
  }
  if (action == GLFW_RELEASE) {
    keys[key] = false;
  }
};
GLfloat deltaTime;
GLfloat lastTime;
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
void do_movement() {
  if (keys[GLFW_KEY_LEFT_SHIFT]) {
    deltaTime *= 2;
  }
  if (keys[GLFW_KEY_W]) {
    cam.processKeyBoard(Camera::FORWARD, deltaTime);
  }
  if (keys[GLFW_KEY_S]) {
    cam.processKeyBoard(Camera::BACKWARD, deltaTime);
  }
  if (keys[GLFW_KEY_A]) {
    cam.processKeyBoard(Camera::LEFT, deltaTime);
  }
  if (keys[GLFW_KEY_D]) {
    cam.processKeyBoard(Camera::RIGHT, deltaTime);
  }
  if (keys[GLFW_KEY_Q]) {
    cam.processKeyBoard(Camera::DOWN, deltaTime);
  }
  if (keys[GLFW_KEY_E]) {
    cam.processKeyBoard(Camera::UP, deltaTime);
  }
}

GLfloat lastX = 400.0f, lastY = 300.0f;
GLboolean firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  GLfloat xOffset = xpos - lastX;
  GLfloat yOffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  cam.processMouseMovement(xOffset, yOffset);
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
  cam.processMouseScroll(yOffset);
}


int main(int argc, const char * argv[]) {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("EX_GS_T_1");
  if (window == nullptr) {
    std::cout << "Create window failed" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  cam.setFPS(GL_TRUE);
  
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
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#ifdef __APPLE__
  string path = "/Camera/1/";
#else
  string path = "\\Camera\\1\\";
#endif
  
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_GS_C_1_Vertex.shader").c_str(), Settings.CCExercisesPath(path + "EX_GS_C_1_Fragment.shader").c_str());
  
  GLuint textures[2];
  TextureReader tex1(Settings.CCResourcesPath("container.jpg").c_str());
  textures[0] = tex1.getTexture();
  TextureReader tex2(Settings.CCResourcesPath("awesomeface.png").c_str());
  textures[1] = tex2.getTexture();

  glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
  };
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;

  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);

  shader.Use();
  GLint modelLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projLoc = glGetUniformLocation(shader.GetProgram(), "projMat");

  glEnable(GL_DEPTH_TEST);
  
  const GLchar* names[] = {
    "tex1", "tex2",
  };
  GLint texLocs[2];
  for (int i = 0; i < 2; i++) {
    texLocs[i] = glGetUniformLocation(shader.GetProgram(), names[i]);
  }
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLfloat currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    do_movement();

    shader.Use();
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(texLocs[i], i);
    }

    glBindVertexArray(VAO);
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);
    for (int i = 0; i < 10; i++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, cubePositions[i]);
      modelMat = glm::rotate(modelMat, glm::radians(currentTime * -90.0f), glm::vec3(0.5f, 1.0f, -0.5f));
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
      glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  return 0;
}
