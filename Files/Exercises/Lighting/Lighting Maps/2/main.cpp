//
//  main.cpp
//  EX_L_LM_2
//
//  Created by King on 16/7/3.
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
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  int width, height;
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
  
#ifdef __APPLE__
  string path = "/Lighting Maps/2";
#else
  string path = "\\Lighting Maps\\2";
#endif

  TextureReader tex1(Settings.CCExercisesPath(path + "container2.png").c_str());
  TextureReader tex2(Settings.CCExercisesPath(path + "container2_specular.png").c_str());
  GLuint tex[2];
  tex[0] = tex1.getTexture();
  tex[2] = tex2.getTexture();
  
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_L_LM_2.vert").c_str(), Settings.CCExercisesPath(path + "EX_L_LM_2.frag").c_str());
  ShaderReader lightShader(Settings.CCExercisesPath(path + "EX_L_LM_2_light.vert").c_str(), Settings.CCExercisesPath(path + "EX_L_LM_2_light.frag").c_str());
  
  glm::vec3 lightColor(1.0f);
  
  shader.Use();
  
  lightShader.Use();
  GLint 
}
