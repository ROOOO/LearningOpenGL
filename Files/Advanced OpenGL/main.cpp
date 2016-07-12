//
//  main.cpp
//  Advanced OpenGL
//
//  Created by King on 16/7/9.
//  Copyright © 2016年 King. All rights reserved.
//

// test1 Depth Testing
// test2 Stencil Testing
// test3 Blending Grass
// test4 Blending Windows
// test5 Face culling
// test6 Framebuffers

#define advancedtest 6

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
  
#if advancedtest != 5
  GLfloat cubeVertices[] = {
    // Positions          // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };
  GLfloat planeVertices[] = {
    // Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    5.0f,  -0.5f, -5.0f,  2.0f, 2.0f
  };
#else
  GLfloat cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    // Right face
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
  };
#endif
#if advancedtest == 3 || advancedtest == 4
  GLfloat vegetationVertices[] = {
    0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  };
#endif
#if advancedtest == 6
  GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // Positions   // TexCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    
    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
  };
#endif
  
  GLuint cubeVAO, cubeVBO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
#if advancedtest != 5
  GLuint planeVAO, planeVBO;
  glGenVertexArrays(1, &planeVAO);
  glGenBuffers(1, &planeVBO);
  glBindVertexArray(planeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif
  
#if advancedtest == 3 || advancedtest == 4
#if advancedtest == 3
  GLuint vegetationVAO, vegetationVBO;
  glGenVertexArrays(1, &vegetationVAO);
  glGenBuffers(1, &vegetationVBO);
  glBindVertexArray(vegetationVAO);
  glBindBuffer(GL_ARRAY_BUFFER, vegetationVBO);
#elif advancedtest == 4
  GLuint windowsVAO, windowsVBO;
  glGenVertexArrays(1, &windowsVAO);
  glGenBuffers(1, &windowsVBO);
  glBindVertexArray(windowsVAO);
  glBindBuffer(GL_ARRAY_BUFFER, windowsVBO);
#endif
  glBufferData(GL_ARRAY_BUFFER, sizeof(vegetationVertices), vegetationVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif
  
#if advancedtest == 6
  GLuint quadVAO, quadVBO;
  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &quadVBO);
  glBindVertexArray(quadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif

#if advancedtest != 6
  TextureReader cubeTex(Settings.CCResourcesPath("marble.jpg").c_str());
#elif advancedtest == 6
  TextureReader cubeTex(Settings.CCResourcesPath("container.jpg").c_str());
#endif
  TextureReader planeTex(Settings.CCResourcesPath("metal.png").c_str());
  GLuint cubeTexture = cubeTex.getTexture();
  GLuint planeTexture = planeTex.getTexture();

#if advancedtest == 3
  TextureReader vegetationTex(Settings.CCResourcesPath("grass.png").c_str(), true);
  GLuint vegetationTexture = vegetationTex.getTexture();
  vector<glm::vec3> vegetation;
  vegetation.push_back(glm::vec3(-1.5f,  0.0f, -0.48f));
  vegetation.push_back(glm::vec3( 1.5f,  0.0f,  0.51f));
  vegetation.push_back(glm::vec3( 0.0f,  0.0f,  0.7f));
  vegetation.push_back(glm::vec3(-0.3f,  0.0f, -2.3f));
  vegetation.push_back(glm::vec3( 0.5f,  0.0f, -0.6f));
#elif advancedtest == 4
  TextureReader windowTex(Settings.CCResourcesPath("window.png").c_str(), true);
  GLuint windowTexture = windowTex.getTexture();
  vector<glm::vec3> windows;
  windows.push_back(glm::vec3(-1.5f,  0.0f, -0.48f));
  windows.push_back(glm::vec3( 1.5f,  0.0f,  0.51f));
  windows.push_back(glm::vec3( 0.0f,  0.0f,  0.7f));
  windows.push_back(glm::vec3(-0.3f,  0.0f, -2.3f));
  windows.push_back(glm::vec3( 0.5f,  0.0f, -0.6f));
#endif

#if advancedtest != 5
  ShaderReader shader(Settings.CCShadersPath("test1.vert").c_str(), Settings.CCShadersPath("test1.frag").c_str());
#elif advancedtest == 5
  ShaderReader shader(Settings.CCShadersPath("test5.vert").c_str(), Settings.CCShadersPath("test5.frag").c_str());
#endif
#if advancedtest == 2
  ShaderReader shaderSingleColor(Settings.CCShadersPath("test2.vert").c_str(), Settings.CCShadersPath("test2.frag").c_str());
  shaderSingleColor.Use();
  GLint singleModelMatLoc = glGetUniformLocation(shaderSingleColor.GetProgram(), "modelMat");
  GLint singleviewMatLoc = glGetUniformLocation(shaderSingleColor.GetProgram(), "viewMat");
  GLint singleprojMatLoc = glGetUniformLocation(shaderSingleColor.GetProgram(), "projMat");
#elif advancedtest == 3
  ShaderReader vegetationShader(Settings.CCShadersPath("test3.vert").c_str(), Settings.CCShadersPath("test3.frag").c_str());
  vegetationShader.Use();
  GLint vegetationModelMatLoc = glGetUniformLocation(vegetationShader.GetProgram(), "modelMat");
  GLint vegetationViewMatLoc = glGetUniformLocation(vegetationShader.GetProgram(), "viewMat");
  GLint vegetationProjMatLoc = glGetUniformLocation(vegetationShader.GetProgram(), "projMat");
#elif advancedtest == 4
  ShaderReader windowsShader(Settings.CCShadersPath("test4.vert").c_str(), Settings.CCShadersPath("test4.frag").c_str());
  windowsShader.Use();
  GLint windowsModelMatLoc = glGetUniformLocation(windowsShader.GetProgram(), "modelMat");
  GLint windowsViewMatLoc = glGetUniformLocation(windowsShader.GetProgram(), "viewMat");
  GLint windowsProjMatLoc = glGetUniformLocation(windowsShader.GetProgram(), "projMat");
#elif advancedtest == 6
  ShaderReader screenShader(Settings.CCShadersPath("test6.vert").c_str(), Settings.CCShadersPath("test6.frag").c_str());
#endif
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;
  
  shader.Use();
  GLint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
  
  glDepthFunc(GL_LESS);
  
#if advancedtest == 2
  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
#endif
  
#if advancedtest == 4
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
  
#if advancedtest == 5
  glEnable(GL_CULL_FACE);
//  glCullFace(GL_FRONT);
  glFrontFace(GL_CW);
#endif
  
#if advancedtest == 6
  GLuint framebuffer;
  glGenFramebuffers(1, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  
  GLuint textureColorBuffer;
  glGenTextures(1, &textureColorBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
  
  GLuint RBO;
  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
  
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Frame Buffer Failed.\n" << std::endl;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    do_movement();
    
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
#if advancedtest == 6
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
#endif
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
#if advancedtest == 1 || advancedtest == 3 || advancedtest == 4 || advancedtest == 5 || advancedtest == 6
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#elif advancedtest == 2
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif
    
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);

    shader.Use();
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
#if advancedtest == 2
    shaderSingleColor.Use();
    glUniformMatrix4fv(singleviewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(singleprojMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
#elif advancedtest == 3
    vegetationShader.Use();
    glUniformMatrix4fv(vegetationViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(vegetationProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
#elif advancedtest == 4
    windowsShader.Use();
    glUniformMatrix4fv(windowsViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(windowsProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
#endif

#if advancedtest == 1 || advancedtest == 3 || advancedtest == 4 || advancedtest == 6
    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.01f, -1.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.01f, 0.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindTexture(GL_TEXTURE_2D, planeTexture);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
#if advancedtest == 3 || advancedtest == 4
#if advancedtest == 3
    vegetationShader.Use();
    glBindVertexArray(vegetationVAO);
    glBindTexture(GL_TEXTURE_2D, vegetationTexture);
    for (GLuint i = 0; i < vegetation.size(); i++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, vegetation[i]);
      glUniformMatrix4fv(vegetationModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glDrawArrays(GL_TRIANGLES, 0, 6);
    }
#elif advancedtest == 4
    windowsShader.Use();
    glBindVertexArray(windowsVAO);
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    map<GLfloat, glm::vec3> sorted;
    for (GLuint i = 0; i < windows.size(); i++) {
      GLfloat distance = glm::length(cam.getPosition() - windows[i]);
      sorted[distance] = windows[i];
    }
    for (map<GLfloat, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, it->second);
      glUniformMatrix4fv(windowsModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
      glDrawArrays(GL_TRIANGLES, 0, 6);
    }
#endif
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
#endif
    
#elif advancedtest == 2
    
    glStencilMask(0x00);
    
    shader.Use();
    glBindVertexArray(planeVAO);
    glBindTexture(GL_TEXTURE_2D, planeTexture);
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glStencilFunc(GL_ALWAYS, 1, 0xff);
    glStencilMask(0xff);
    
    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.01f, -1.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.01f, 0.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glStencilFunc(GL_NOTEQUAL, 1, 0xff);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    
    shaderSingleColor.Use();
    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.01f, -1.0f));
    modelMat = glm::scale(modelMat, glm::vec3(1.1f));
    glUniformMatrix4fv(singleModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.01f, 0.0f));
    modelMat = glm::scale(modelMat, glm::vec3(1.1f));
    glUniformMatrix4fv(singleModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glStencilMask(0xff);
    glEnable(GL_DEPTH_TEST);
    
#elif advancedtest == 5
    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
#endif
    
#if advancedtest == 6
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    
    screenShader.Use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
#endif
    
    glfwSwapBuffers(window);
  }

  return 0;
}
