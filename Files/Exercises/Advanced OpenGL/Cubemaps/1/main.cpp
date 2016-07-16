//
//  main.cpp
//  EX_AO_CM
//
//  Created by King on 16/7/16.
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
  
  GLfloat skyboxVertices[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
  };
  
  GLuint skyboxVAO, skyboxVBO;
  glGenVertexArrays(1, &skyboxVAO);
  glGenBuffers(1, &skyboxVBO);
  glBindVertexArray(skyboxVAO);
  glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#ifdef __APPLE__
  string path = "skybox/";
#else
  string path = "skybox\\"
#endif
  vector<string> faces;
  faces.push_back(Settings.CCResourcesPath(path + "right.jpg"));
  faces.push_back(Settings.CCResourcesPath(path + "left.jpg"));
  faces.push_back(Settings.CCResourcesPath(path + "top.jpg"));
  faces.push_back(Settings.CCResourcesPath(path + "bottom.jpg"));
  faces.push_back(Settings.CCResourcesPath(path + "back.jpg"));
  faces.push_back(Settings.CCResourcesPath(path + "front.jpg"));
  
  TextureReader skyboxTex(faces);
  GLuint skyboxTexture = skyboxTex.getCubeMap();
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;
  
#ifdef __APPLE__
  string exercisePath = "Cubemaps/1/";
#else
  string exercisePath = "Cubemaps\\1\\";
#endif
  ShaderReader shader(Settings.CCExercisesPath(exercisePath + "EX_AO_CM.vert").c_str(), Settings.CCExercisesPath(exercisePath + "EX_AO_CM.frag").c_str());
  shader.Use();
  GLuint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLuint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLuint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
  GLuint viewPosLoc = glGetUniformLocation(shader.GetProgram(), "viewPos");
  GLuint textureLoc = glGetUniformLocation(shader.GetProgram(), "tex");
  
  ShaderReader skyboxShader(Settings.CCExercisesPath(exercisePath + "EX_AO_CM_skybox.vert").c_str(), Settings.CCExercisesPath(exercisePath + "EX_AO_CM_skybox.frag").c_str());
  skyboxShader.Use();
  GLuint skyboxViewMatLoc = glGetUniformLocation(skyboxShader.GetProgram(), "viewMat");
  GLuint skyboxProjMatLoc = glGetUniformLocation(skyboxShader.GetProgram(), "projMat");

  Model model(Settings.CCModelsPath("Nanosuit/nanosuit.obj").c_str());
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    do_movement();
    
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    
    shader.Use();
    viewMat = cam.getViewMatrix();
    modelMat = glm::mat4();
    modelMat = glm::rotate(modelMat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMat = glm::scale(modelMat, glm::vec3(0.2f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glUniform3f(viewPosLoc, cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
    glActiveTexture(GL_TEXTURE3);
    glUniform1i(textureLoc, 3);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    model.Draw(shader);
    
    glDepthFunc(GL_LEQUAL);
    skyboxShader.Use();
    viewMat = glm::mat4(glm::mat3(cam.getViewMatrix()));
    glUniformMatrix4fv(skyboxViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(skyboxProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    glBindVertexArray(skyboxVAO);
//    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthFunc(GL_LESS);
   
    glfwSwapBuffers(window);
  }
}