//
//  main.cpp
//  Lighting
//
//  Created by King on 16/6/27.
//  Copyright © 2016年 King. All rights reserved.
//

#include <iostream>
#include "CommonSettings.hpp"

// test1 basic lighting
// test2 material
// test3 lighting maps
// test4 Direction Light
// test5 Point Light
// test6 Spot Light

#define test 6

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
  
#if test == 1 || test == 2
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
#elif test == 3 || test == 4 || test == 5 || test == 6
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
#endif
  
  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#if test == 2 || test == 1
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
#elif test == 3 || test == 4 || test == 5 || test == 6
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
#endif
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  GLuint lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
#if test == 1 || test == 2
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
#elif test == 3 || test == 4 || test == 5 | test == 6
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
#endif
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#if test == 1
  ShaderReader shader(Settings.CCShadersPath("shader_test1.vs").c_str(), Settings.CCShadersPath("shader_test1.frag").c_str());
#elif test == 2
  ShaderReader shader(Settings.CCShadersPath("shader_test2.vs").c_str(), Settings.CCShadersPath("shader_test2.frag").c_str());
#elif test == 3
  ShaderReader shader(Settings.CCShadersPath("shader_test3.vs").c_str(), Settings.CCShadersPath("shader_test3.frag").c_str());
#elif test == 4
  ShaderReader shader(Settings.CCShadersPath("shader_test4.vs").c_str(), Settings.CCShadersPath("shader_test4.frag").c_str());
#elif test == 5
  ShaderReader shader(Settings.CCShadersPath("shader_test5.vs").c_str(), Settings.CCShadersPath("shader_test5.frag").c_str());
#elif test == 6
  ShaderReader shader(Settings.CCShadersPath("shader_test6.vs").c_str(), Settings.CCShadersPath("shader_test6.frag").c_str());
#endif
  ShaderReader lightShader(Settings.CCShadersPath("shader_test1_light.vs").c_str(), Settings.CCShadersPath("shader_test1_light.frag").c_str());

#if test == 3 || test == 4 || test == 5 || test == 6
  GLuint tex[2];
  TextureReader tex0(Settings.CCResourcesPath("container2.png").c_str());
  TextureReader tex1(Settings.CCResourcesPath("container2_specular.png").c_str());
  tex[0] = tex0.getTexture();
  tex[1] = tex1.getTexture();
#endif
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;

  glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
  glm::vec3 lightAmbient(0.2f);
  glm::vec3 lightDiffuse(0.5f);

#if test == 2 || test == 3 || test == 4 || test == 5 || test == 6
#if test == 2
  glm::vec3 ambient(0.0215f, 0.1745f, 0.0215f);
  glm::vec3 diffuse(0.07568f, 0.61424f, 0.07568f);
  glm::vec3 specular(0.633f, 0.727811f, 0.633f);
#endif
  GLfloat shininess = 0.6f * 128;
#endif
  
  shader.Use();
  GLint modelLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
#if test == 1
  GLint objectColorLoc = glGetUniformLocation(shader.GetProgram(), "objectColor");
  GLint lightPosLoc = glGetUniformLocation(shader.GetProgram(), "lightPos");
  GLint lightColorLoc = glGetUniformLocation(shader.GetProgram(), "lightColor");
#endif
  GLint viewPosLoc = glGetUniformLocation(shader.GetProgram(), "viewPos");
#if test == 2 || test == 3 || test == 4 || test == 5 || test == 6
#if test == 2
  GLint ambientLoc = glGetUniformLocation(shader.GetProgram(), "material.ambient");
#endif
  GLint diffuseLoc = glGetUniformLocation(shader.GetProgram(), "material.diffuse");
  GLint specularLoc = glGetUniformLocation(shader.GetProgram(), "material.specular");
  GLint shininessLoc = glGetUniformLocation(shader.GetProgram(), "material.shininess");
  glUniform1i(diffuseLoc, 0);
  glUniform1i(specularLoc, 1);
  
  GLint lightAmbientLoc = glGetUniformLocation(shader.GetProgram(), "light.ambient");
  GLint lightDiffuseLoc = glGetUniformLocation(shader.GetProgram(), "light.diffuse");
  GLint lightSpecularLoc = glGetUniformLocation(shader.GetProgram(), "light.specular");
#if test == 2 || test == 3 || test == 5 || test == 6
  GLint lightPosLoc = glGetUniformLocation(shader.GetProgram(), "light.position");
#if test == 2 || test == 3
  glUniform3f(lightPosLoc, lightPos.r, lightPos.g, lightPos.b);
#endif 
#if test == 5 || test == 6
  GLint lightConstantLoc = glGetUniformLocation(shader.GetProgram(), "light.constant");
  GLint lightLinearLoc = glGetUniformLocation(shader.GetProgram(), "light.linear");
  GLint lightQuadraticLoc = glGetUniformLocation(shader.GetProgram(), "light.quadratic");
  glUniform1f(lightConstantLoc, 1.0f);
  glUniform1f(lightLinearLoc, 0.09f);
  glUniform1f(lightQuadraticLoc, 0.032f);
#if test == 6
  GLint lightDirectionLoc = glGetUniformLocation(shader.GetProgram(), "light.direction");
  GLint lightCutOffLoc = glGetUniformLocation(shader.GetProgram(), "light.cutOff");
  glUniform1f(lightCutOffLoc, glm::cos(glm::radians(12.5f)));
#endif
#endif
#elif test == 4 
  GLint lightDirectionLoc = glGetUniformLocation(shader.GetProgram(), "light.direction");
  glUniform3f(lightDirectionLoc, -0.2f, -1.0f, -0.3f);
#endif
#endif

  lightShader.Use();
  GLint lightModelLoc = glGetUniformLocation(lightShader.GetProgram(), "modelMat");
  GLint lightViewLoc = glGetUniformLocation(lightShader.GetProgram(), "viewMat");
  GLint lightProjLoc = glGetUniformLocation(lightShader.GetProgram(), "projMat");
  GLint lightLightColorLoc = glGetUniformLocation(lightShader.GetProgram(), "lightColor");

#if test == 2 || test == 3 || test == 4 || test == 5 || test == 6
  glm::vec3 lightSpecular(1.0f);
#endif
#if test == 4 || test == 5 || test == 6
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
#endif
  
  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    do_movement();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLfloat currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;
    
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(glm::radians(cam.getZoom()), (GLfloat)width / height, 0.1f, 100.0f);
    
    shader.Use();
    modelMat = glm::mat4();
#if test == 1 ||  test == 2 || test == 3
    modelMat = glm::rotate(modelMat, glm::radians(currentTime * 50), glm::vec3(0.5f, 1.0f, -0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
#endif
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));

#if test == 2
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);
    lightDiffuse *= lightColor;
    lightAmbient *= lightDiffuse;
#endif

    glUniform3f(viewPosLoc, cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
    
#if test == 1
    glUniform3f(objectColorLoc, objectColor.r, objectColor.g, objectColor.b);
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b);
#elif test == 2 || test == 3 || test == 4 || test == 5 || test == 6
#if test == 2
    glUniform3f(ambientLoc, ambient.r, ambient.g, ambient.b);
    glUniform3f(diffuseLoc, diffuse.r, diffuse.g, diffuse.b);
    glUniform3f(specularLoc, specular.r, specular.g, specular.b);
#elif test == 3 || test == 4 || test == 5 || test == 6 
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, tex[i]);
    }
#endif
    
    glUniform1f(shininessLoc, shininess);
    
    glUniform3f(lightAmbientLoc, lightAmbient.r, lightAmbient.g, lightAmbient.b);
    glUniform3f(lightDiffuseLoc, lightDiffuse.r, lightDiffuse.g, lightDiffuse.b);
    glUniform3f(lightSpecularLoc, lightSpecular.r, lightSpecular.g, lightSpecular.b);

#if test == 6
    glUniform3f(lightPosLoc, cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
    glUniform3f(lightDirectionLoc, cam.getDirection().x, cam.getDirection().y, cam.getDirection().z);
#endif

#endif
    glBindVertexArray(VAO);
#if test == 1 || test == 2 || test == 3
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
#elif test == 4 || test == 5 || test == 6
    for (int i = 0; i < 10; i++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, glm::vec3(cubePositions[i]));
      modelMat = glm::rotate(modelMat, glm::radians(currentTime * 50), glm::vec3(0.5f, 1.0f, -0.5f));
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
#endif
    
    lightShader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, lightPos);
    modelMat = glm::scale(modelMat, glm::vec3(0.2f));
    
    glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(lightProjLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    
    glUniform3f(lightLightColorLoc, lightColor.r, lightColor.g, lightColor.b);
    
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  
  return 0;
}
