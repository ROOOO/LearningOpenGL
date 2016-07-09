//
//  main.cpp
//  EX_ML_M
//
//  Created by King on 16/7/9.
//  Copyright © 2016年 King. All rights reserved.
//

#include "CommonSettings.hpp"

Camera cam(glm::vec3(0.0f, 0.0f, 5.0f));
GLboolean keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
  }
  if (action == GLFW_PRESS) {
    keys[key] = true;
  }
  if (action == GLFW_RELEASE) {
    keys[key] = false;
  }
};
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
  GLFWwindow *window = Settings.CreateWindow();
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    glfwTerminate();
    return -1;
  }
  
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  
  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);
  
#ifdef __APPLE__
  string path = "EX_ML_M/";
#else
  string path = "EX_ML_M\\";
#endif
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_ML_M.vert").c_str(), Settings.CCExercisesPath(path + "EX_ML_M.frag").c_str());
  Model model(Settings.CCModelsPath("deathKnight/deathKnight.obj").c_str());
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;
  GLfloat shininess = 1.0f;
  glm::vec3 pointLightPositions[] = {
    glm::vec3(2.3f, -1.6f, -3.0f),
    glm::vec3(-1.7f, 0.9f, 1.0f)
  };
  
  shader.Use();
  GLint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
  
  glUniform1f(glGetUniformLocation(shader.GetProgram(), "material.shininess"), shininess);
  
  string prefix = "pointLights[";
  for (GLuint i = 0; i < 2; i++) {
    stringstream ss;
    ss << i;
    string num;
    ss >> num;
    glUniform3f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
    glUniform3f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].ambient").c_str()), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].diffuse").c_str()), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].constant").c_str()), 1.0f);
    glUniform1f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].linear").c_str()), 0.009f);
    glUniform1f(glGetUniformLocation(shader.GetProgram(), (prefix + num + "].quadratic").c_str()), 0.0032f);
  }
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    do_movement();
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);
    
    modelMat = glm::mat4();
    modelMat = glm::scale(modelMat, glm::vec3(0.2f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    
    model.Draw(shader);
    
    glfwSwapBuffers(window);
  }
  
  return 0;
}
