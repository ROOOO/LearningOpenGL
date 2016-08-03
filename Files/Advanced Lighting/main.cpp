//
//  main.cpp
//  Advanced Lighting
//
//  Created by King on 16/7/24.
//  Copyright © 2016年 King. All rights reserved.
//

#include "CommonSettings.hpp"

Camera cam(glm::vec3(0.0f, 0.0f, 5.0f));
GLboolean keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
CommonSettings Settings;
GLboolean blinn = true;
GLboolean _gamma = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
  }
  if (key == GLFW_KEY_B && action == GLFW_PRESS) {
    blinn = !blinn;
  }
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    _gamma = !_gamma;
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

// test1 Blinn-Phong Lighting
// test2 Gamma Correction
// test3 Gamma Attanuation
// test4 Shadow Mapping

#define test 4

#if test == 4
void RenderScene(ShaderReader &shader);
void RenderQuad();
void RenderCube();
#endif

int main(int argc, const char * argv[]) {
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
  
  GLfloat planeVertices[] = {
    // Positions          // Normals         // Texture Coords
    8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
    -8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
    
    8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
    -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
    8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
  };
  glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
  
  GLuint planeVAO, planeVBO;
  glGenVertexArrays(1, &planeVAO);
  glGenBuffers(1, &planeVBO);
  glBindVertexArray(planeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

#if test == 4
  GLuint depthMapFBO;
  glGenFramebuffers(1, &depthMapFBO);
  
  const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
  GLuint depthMap;
  glGenTextures(1, &depthMap);
  glBindTexture(GL_TEXTURE_2D, depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
  
#if test == 1
  ShaderReader shader(Settings.CCShadersPath("test1.vert").c_str(), Settings.CCShadersPath("test1.frag").c_str());
#elif test == 2
  ShaderReader shader(Settings.CCShadersPath("test2.vert").c_str(), Settings.CCShadersPath("test2.frag").c_str());
#elif test == 3
  ShaderReader shader(Settings.CCShadersPath("test3.vert").c_str(), Settings.CCShadersPath("test3.frag").c_str());
#elif test == 4
  ShaderReader shader(Settings.CCShadersPath("test4.vert").c_str(), Settings.CCShadersPath("test4.frag").c_str());
  ShaderReader shaderDepthMap(Settings.CCShadersPath("test4_depth.vert").c_str(), Settings.CCShadersPath("test4_depth.frag").c_str());
  GLuint lightSpaceMatLoc = glGetUniformLocation(shaderDepthMap.GetProgram(), "lightSpaceMat");

#endif

  shader.Use();
  GLuint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLuint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLuint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
  
  TextureReader planeTex(Settings.CCResourcesPath("wood.png").c_str());
  GLuint planeTexture = planeTex.getTexture();
  TextureReader gammaCorrectionplaneTex(Settings.CCResourcesPath("wood.png").c_str(), false, true);
  GLuint gammaCorrectionplaneTexture = gammaCorrectionplaneTex.getTexture();
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;
  
#if test == 2
  //glEnable(GL_FRAMEBUFFER_SRGB);
#endif
  
#if test == 3
  glm::vec3 lightPositions[] = {
    glm::vec3(-3.0f, 0.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, 0.0f),
    glm::vec3( 1.0f, 0.0f, 0.0f),
    glm::vec3( 3.0f, 0.0f, 0.0f)
  };
  glm::vec3 lightColors[] = {
    glm::vec3(0.25),
    glm::vec3(0.50),
    glm::vec3(0.75),
    glm::vec3(1.00)
  };
#endif

#if test == 4
  lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
#endif
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    do_movement();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
#if test != 4
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);
    
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glUniform3f(glGetUniformLocation(shader.GetProgram(), "viewPos"), cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);

#if test == 1 && test == 2
    glUniform3f(glGetUniformLocation(shader.GetProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
#endif
#if test == 2
    glUniform1d(glGetUniformLocation(shader.GetProgram(), "blinn"), blinn);
#endif
#if test == 3
    glUniform3fv(glGetUniformLocation(shader.GetProgram(), "lightPos"), 4, &lightPositions[0][0]);
    glUniform3fv(glGetUniformLocation(shader.GetProgram(), "lightColor"), 4, &lightColors[0][0]);
    glUniform1d(glGetUniformLocation(shader.GetProgram(), "gamma"), _gamma);
#endif

    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindTexture(GL_TEXTURE_2D, _gamma ? gammaCorrectionplaneTexture : planeTexture);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
#endif

#if test == 4
    glm::mat4 lightProjMat, lightViewMat;
    glm::mat4 lightSpaceMat;
    GLfloat nearPlane = 1.0f, farPlane = 7.5f;
    lightProjMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
    lightViewMat = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lightSpaceMat = lightProjMat * lightViewMat;
    shaderDepthMap.Use();
    glUniformMatrix4fv(lightSpaceMatLoc, 1, GL_FALSE, glm::value_ptr(lightSpaceMat));

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    RenderScene(shaderDepthMap);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    RenderQuad();
#endif
    
    glfwSwapBuffers(window);
  }
  return 0;
}

#if test == 4
void RenderScene(ShaderReader &shader) {

}
#endif
