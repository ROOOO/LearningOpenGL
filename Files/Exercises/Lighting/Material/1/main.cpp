//
//  main.cpp
//  EX_L_M
//
//  Created by King on 16/6/30.
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
  if (nullptr == window) {
    glfwTerminate();
    return -1;
  }
  
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
    
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
  };
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  GLuint lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#ifdef __APPLE__
  string path = "/Material/1/";
#else
  string path = "\\Material\\1\\";
#endif
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_L_M_1.vert").c_str(), Settings.CCExercisesPath(path + "EX_L_M_1.frag").c_str());
  ShaderReader lightShader(Settings.CCExercisesPath(path + "EX_L_M_1_light.vert").c_str(), Settings.CCExercisesPath(path + "EX_L_M_1_light.frag").c_str());
  
  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);

  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;
  
  glm::vec3 materialAmbientColor(0.135f, 0.2225f, 0.1575f);
  glm::vec3 materialDiffuseColor(0.54f, 0.89f, 0.63f);
  glm::vec3 materialSpecularColor(0.316228f);
  GLfloat materialShininess = 0.1f * 128;
  
  glm::vec3 lightAmbient(1.0f);
  glm::vec3 lightDiffuse(1.0f);
  glm::vec3 lightSpecular(1.0f);
  
  shader.Use();
  GLint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
  GLint viewPosLoc = glGetUniformLocation(shader.GetProgram(), "viewPos");
  
  GLint materialAmbientColorLoc = glGetUniformLocation(shader.GetProgram(), "material.ambient");
  GLint materialDiffuseColorLoc = glGetUniformLocation(shader.GetProgram(), "material.diffuse");
  GLint materialSpecularColorLoc = glGetUniformLocation(shader.GetProgram(), "material.specular");
  GLint materialShininessLoc = glGetUniformLocation(shader.GetProgram(), "material.shininess");
  
  GLint lightAmbientColorLoc = glGetUniformLocation(shader.GetProgram(), "light.ambient");
  GLint lightDiffuseColorLoc = glGetUniformLocation(shader.GetProgram(), "light.diffuse");
  GLint lightSpecularColorLoc = glGetUniformLocation(shader.GetProgram(), "light.specular");
  GLint lightPosLoc = glGetUniformLocation(shader.GetProgram(), "light.position");
  
  lightShader.Use();
  GLint lightModelMatLoc = glGetUniformLocation(lightShader.GetProgram(), "modelMat");
  GLint lightViewMatLoc = glGetUniformLocation(lightShader.GetProgram(), "viewMat");
  GLint lightProjMatLoc = glGetUniformLocation(lightShader.GetProgram(), "projMat");
  GLint lightLightColorLoc = glGetUniformLocation(lightShader.GetProgram(), "lightColor");
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    do_movement();
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);
    
    shader.Use();
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    
    glUniform3f(viewPosLoc, cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
    glUniform3f(materialAmbientColorLoc, materialAmbientColor.r, materialAmbientColor.g, materialAmbientColor.b);
    glUniform3f(materialDiffuseColorLoc, materialDiffuseColor.r, materialDiffuseColor.g, materialDiffuseColor.b);
    glUniform3f(materialSpecularColorLoc, materialSpecularColor.r, materialSpecularColor.g, materialSpecularColor.b);
    glUniform1f(materialShininessLoc, materialShininess);
    glUniform3f(lightAmbientColorLoc, lightAmbient.r, lightAmbient.g, lightAmbient.b);
    glUniform3f(lightDiffuseColorLoc, lightDiffuse.r, lightDiffuse.g, lightDiffuse.b);
    glUniform3f(lightSpecularColorLoc, lightSpecular.r, lightSpecular.g, lightSpecular.b);
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    lightShader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, lightPos);
    modelMat = glm::scale(modelMat, glm::vec3(0.2f));
    glUniformMatrix4fv(lightModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(lightViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(lightProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glUniform3f(lightLightColorLoc, lightColor.r, lightColor.g, lightColor.b);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
}
