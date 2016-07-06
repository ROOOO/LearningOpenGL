//
//  main.cpp
//  EX_L_ML_1
//
//  Created by King on 16/7/6.
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

  GLfloat vertices[] = {
    // Positions           // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
  };
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  GLuint lampVAO;
  glGenVertexArrays(1, &lampVAO);
  glBindVertexArray(lampVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#ifdef __APPLE__
  string path = "/Multiple Lights/1/";
#else
  string path = "\\Multiple Lights\\1\\";
#endif

  ShaderReader shader(Settings.CCExercisesPath(path + "EX_L_ML_1.vert").c_str(), Settings.CCExercisesPath(path + "EX_L_ML_1.frag").c_str());
  ShaderReader lampShader(Settings.CCExercisesPath(path + "EX_L_ML_1_lamp.vert").c_str(), Settings.CCExercisesPath(path + "EX_L_ML_1_lamp.frag").c_str());
  
  GLuint tex[2];
  TextureReader tex0(Settings.CCExercisesPath(path + "container2.png").c_str());
  TextureReader tex1(Settings.CCExercisesPath(path + "container2_specular.png").c_str());
  tex[0] = tex0.getTexture();
  tex[1] = tex1.getTexture();

  glm::mat4 modelMat, viewMat, projMat;
  glm::vec3 lightAmbient(0.2f);
  glm::vec3 lightDiffuse(0.5f);
  glm::vec3 lightSpecular(1.0f);
  
  GLfloat shininess = 0.6f * 128;
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

  glm::vec3 lampColor(1.0f);
  glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)
  };

  shader.Use();
  GLuint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLuint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLuint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
  
  for (int i = 0; i < 2; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, tex[i]);
  }
  glUniform1i(glGetUniformLocation(shader.GetProgram(), "material.diffuse"), 0);
  glUniform1i(glGetUniformLocation(shader.GetProgram(), "material.specular"), 1);
  glUniform1f(glGetUniformLocation(shader.GetProgram(), "material.shininess"), shininess);
  
  glUniform3f(glGetUniformLocation(shader.GetProgram(), "directionLight.direction"), -0.2f, -1.0f, -0.3f);
  glUniform3f(glGetUniformLocation(shader.GetProgram(), "directionLight.ambient"), lightAmbient.r, lightAmbient.g, lightAmbient.b);
  glUniform3f(glGetUniformLocation(shader.GetProgram(), "directionLight.diffuse"), lightDiffuse.r, lightDiffuse.g, lightDiffuse.b);
  glUniform3f(glGetUniformLocation(shader.GetProgram(), "directionLight.specular"), lightSpecular.r, lightSpecular.g, lightSpecular.b);
  
  lampShader.Use();
  GLuint lampModelMatLoc = glGetUniformLocation(lampShader.GetProgram(), "modelMat");
  GLuint lampViewMatLoc = glGetUniformLocation(lampShader.GetProgram(), "viewMat");
  GLuint lampProjMatLoc = glGetUniformLocation(lampShader.GetProgram(), "projMat");
  glUniform3f(glGetUniformLocation(lampShader.GetProgram(), "lampColor"), lampColor.r, lampColor.g, lampColor.b);
  
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
    
    shader.Use();
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glBindVertexArray(VAO);
    for (int i = 0; i < 10; i++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, cubePositions[i]);
      modelMat = glm::rotate(modelMat, glm::radians(i * 30.f), glm::vec3(0.5f, 1.0f, -0.5f));
      glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
    
    lampShader.Use();
    glUniformMatrix4fv(lampViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(lampProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glBindVertexArray(lampVAO);
    for (int i = 0; i < 4; i++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, pointLightPositions[i]);
      modelMat = glm::scale(modelMat, glm::vec3(0.2f));
      glUniformMatrix4fv(lampModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  return 0;
}
