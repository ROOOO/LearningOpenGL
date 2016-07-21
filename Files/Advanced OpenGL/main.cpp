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
// test7 Skybox
// test8 Reflection
// test9 Advanced GLSL
// test10 Uniform buffer
// test11 Geometry Shader
// test12 Exploding Objects
// test13 Visualizing normal vectors
// test14 Instancing
// test15 An asteroid field

#define advancedtest 15

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
  
#if advancedtest != 5 && advancedtest != 8 && advancedtest != 11 && advancedtest != 12 && advancedtest != 13 && advancedtest != 14 && advancedtest == 15
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
#if advancedtest < 7
  GLfloat planeVertices[] = {
    // Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    5.0f,  -0.5f, -5.0f,  2.0f, 2.0f
  };
#endif
#elif advancedtest == 5
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
#elif advancedtest == 8
  GLfloat cubeVertices[] = {
    // Positions          // Normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
#if advancedtest == 7 || advancedtest == 8
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
#endif
#if advancedtest == 11
  GLfloat points[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
  };
#endif
#if advancedtest == 14
  GLfloat quadVertices[] = {
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
    0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
    
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
    0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    0.05f,  0.05f,  0.0f, 1.0f, 1.0f,
  };
#endif
  
#if advancedtest != 11 && advancedtest != 12 && advancedtest != 13 && advancedtest != 14 && advancedtest != 15
  GLuint cubeVAO, cubeVBO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
#if advancedtest != 8
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
#else
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
#endif
  glEnableVertexAttribArray(0);
#if advancedtest != 8
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
#else
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
#endif
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif
  
#if advancedtest == 11
  GLuint pointsVAO, pointsVBO;
  glGenVertexArrays(1, &pointsVAO);
  glGenBuffers(1, &pointsVBO);
  glBindVertexArray(pointsVAO);
  glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif
  
#if advancedtest != 5 && advancedtest < 7
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
  
#if advancedtest == 14
  glm::vec2 translations[100];
  GLuint index = 0;
  GLfloat offset = 0.1f;
  for (GLfloat y = -10; y < 10; y += 2) {
    for (GLfloat x = -10; x < 10; x += 2) {
      glm::vec2 translation;
      translation.x = (GLfloat)x / 10.0f + offset;
      translation.y = (GLfloat)y / 10.0f + offset;
      translations[index++] = translation;
    }
  }

  GLuint instanceVBO;
  glGenBuffers(1, &instanceVBO);
  glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, translations, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
  
#if advancedtest == 6 || advancedtest == 14
  GLuint quadVAO, quadVBO;
  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &quadVBO);
  glBindVertexArray(quadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
#if advancedtest == 6
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
#else
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
#endif
  glEnableVertexAttribArray(0);
#if advancedtest == 6
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
#else
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
#endif
  glEnableVertexAttribArray(1);
#if advancedtest == 14
  glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(2);
  glVertexAttribDivisor(2, 1);
#endif
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif
  
#if advancedtest == 7 || advancedtest == 8
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
#endif

#if advancedtest < 6
  TextureReader cubeTex(Settings.CCResourcesPath("marble.jpg").c_str());
#elif advancedtest == 6 || advancedtest == 7
  TextureReader cubeTex(Settings.CCResourcesPath("container.jpg").c_str());
  GLuint cubeTexture = cubeTex.getTexture();
#endif
#if advancedtest < 7
  TextureReader planeTex(Settings.CCResourcesPath("metal.png").c_str());
  GLuint planeTexture = planeTex.getTexture();
#elif advancedtest == 7 || advancedtest == 8
#ifdef __APPLE__
  string path = "skybox/";
#else
  string path = "skybox\\";
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
//  GLuint skyboxTexture = loadCubemap(faces);
#endif

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

#if advancedtest != 5 && advancedtest < 8
  ShaderReader shader(Settings.CCShadersPath("test1.vert").c_str(), Settings.CCShadersPath("test1.frag").c_str());
#elif advancedtest == 5
  ShaderReader shader(Settings.CCShadersPath("test5.vert").c_str(), Settings.CCShadersPath("test5.frag").c_str());
#elif advancedtest == 8
  ShaderReader shader(Settings.CCShadersPath("test8.vert").c_str(), Settings.CCShadersPath("test8.frag").c_str());
  GLint viewPosLoc = glGetUniformLocation(shader.GetProgram(), "viewPos");
#elif advancedtest == 9
  ShaderReader shader(Settings.CCShadersPath("test9.vert").c_str(), Settings.CCShadersPath("test9.frag").c_str());
#elif advancedtest == 10
  ShaderReader redShader(Settings.CCShadersPath("test10.vert").c_str(), Settings.CCShadersPath("test10_red.frag").c_str());
  ShaderReader greenShader(Settings.CCShadersPath("test10.vert").c_str(), Settings.CCShadersPath("test10_green.frag").c_str());
  ShaderReader blueShader(Settings.CCShadersPath("test10.vert").c_str(), Settings.CCShadersPath("test10_blue.frag").c_str());
  ShaderReader yellowShader(Settings.CCShadersPath("test10.vert").c_str(), Settings.CCShadersPath("test10_yellow.frag").c_str());
#elif advancedtest == 11
  ShaderReader shader(Settings.CCShadersPath("test11.vert"), Settings.CCShadersPath("test11.frag"), Settings.CCShadersPath("test11.geom"));
#elif advancedtest == 12
  ShaderReader shader(Settings.CCShadersPath("test12.vert"), Settings.CCShadersPath("test12.frag"), Settings.CCShadersPath("test12.geom"));
  //  ShaderReader shader(Settings.CCShadersPath("test12.vert").c_str(), Settings.CCShadersPath("test12.frag").c_str());
  Model model(Settings.CCModelsPath("deathKnight/deathKnight.obj").c_str());
#elif advancedtest == 13
  ShaderReader shader(Settings.CCShadersPath("test13.vert"), Settings.CCShadersPath("test13.frag"), Settings.CCShadersPath("test13.geom"));
  ShaderReader modelShader(Settings.CCShadersPath("test13_model.vert").c_str(), Settings.CCShadersPath("test13_model.frag").c_str());
//  Model model(Settings.CCModelsPath("deathKnight/deathKnight.obj").c_str());
  Model model(Settings.CCModelsPath("Nanosuit/nanosuit.obj").c_str());
#elif advancedtest == 14
  ShaderReader shader(Settings.CCShadersPath("test14.vert").c_str(), Settings.CCShadersPath("test14.frag").c_str());
#elif advancedtest == 15
  ShaderReader shader(Settings.CCShadersPath("test15.vert").c_str(), Settings.CCShadersPath("test15.frag").c_str());
  ShaderReader instanceShader(Settings.CCShadersPath("test15_instance.vert").c_str(), Settings.CCShadersPath("test15.frag").c_str());
  Model planet(Settings.CCModelsPath("planet/planet.obj").c_str());
  Model rock(Settings.CCModelsPath("deathKnight/deathKnight.obj").c_str());
//  Model rock(Settings.CCModelsPath("rock/rock.obj").c_str());
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
#elif advancedtest == 7 || advancedtest == 8
  ShaderReader skyboxShader(Settings.CCShadersPath("test7.vert").c_str(), Settings.CCShadersPath("test7.frag").c_str());
//  GLint skyboxModelMatLoc = glGetUniformLocation(skyboxShader.GetProgram(), "modelMat");
  GLint skyboxViewMatLoc = glGetUniformLocation(skyboxShader.GetProgram(), "viewMat");
  GLint skyboxProjMatLoc = glGetUniformLocation(skyboxShader.GetProgram(), "projMat");
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  Model model(Settings.CCModelsPath("deathKnight/deathKnight.obj").c_str());
#endif
  
  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;
  
#if advancedtest != 10
  shader.Use();
  GLint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");
#endif
  
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
  
#if advancedtest == 7
  glDepthFunc(GL_LEQUAL);
#endif
  
#if advancedtest == 9
  glEnable(GL_PROGRAM_POINT_SIZE);
#endif
  
#if advancedtest == 10
  GLuint uniformBlockIndexRed = glGetUniformBlockIndex(redShader.GetProgram(), "Matrices");
  GLuint uniformBlockIndexGreen = glGetUniformBlockIndex(greenShader.GetProgram(), "Matrices");
  GLuint uniformBlockIndexBlue = glGetUniformBlockIndex(blueShader.GetProgram(), "Matrices");
  GLuint uniformBlockIndexYellow = glGetUniformBlockIndex(yellowShader.GetProgram(), "Matrices");
  
  glUniformBlockBinding(redShader.GetProgram(), uniformBlockIndexRed, 0);
  glUniformBlockBinding(greenShader.GetProgram(), uniformBlockIndexGreen, 0);
  glUniformBlockBinding(blueShader.GetProgram(), uniformBlockIndexBlue, 0);
  glUniformBlockBinding(yellowShader.GetProgram(), uniformBlockIndexYellow, 0);
  
  GLuint UBO;
  glGenBuffers(1, &UBO);
  glBindBuffer(GL_UNIFORM_BUFFER, UBO);
  glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4));
  
  projMat = glm::perspective(glm::radians(45.0f), (GLfloat)width / height, 0.1f, 100.0f);
  glBindBuffer(GL_UNIFORM_BUFFER, UBO);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(projMat));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
#endif
  
#if advancedtest == 13
  modelShader.Use();
  GLint modelModelMatLoc = glGetUniformLocation(modelShader.GetProgram(), "modelMat");
  GLint modelViewMatLoc = glGetUniformLocation(modelShader.GetProgram(), "viewMat");
  GLint modelProjMatLoc = glGetUniformLocation(modelShader.GetProgram(), "projMat");
#endif
  
#if advancedtest == 14
//  shader.Use();
//  for (GLuint i = 0; i < 100; i++) {
//    stringstream ss;
//    string index;
//    ss << i;
//    index = ss.str();
//    glUniform2f(glGetUniformLocation(shader.GetProgram(), ("offsets[" + index + "]").c_str()), translations[i].x, translations[i].y);
//  }
#endif
  
#if advancedtest == 15
  GLuint amount = 1000;
  glm::mat4 *modelMatrices;
  modelMatrices = new glm::mat4[amount];
  srand(glfwGetTime());
  GLfloat radius = 20.0f;
  GLfloat offset = 2.5f;
  for (GLuint i = 0; i < amount; i++) {
    glm::mat4 model;
    GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
    GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
    GLfloat x = sin(angle) * radius + displacement;
    displacement = (rand() % (GLint)(2 * offset * 100) / 100.0f - offset);
    GLfloat y = displacement * 0.4f;
    displacement = (rand() % (GLint)(2 * offset * 100) / 100.0f - offset);
    GLfloat z = cos(angle) * radius + displacement;
    model = glm::translate(model, glm::vec3(x, y, z));
    GLfloat scale = (rand() % 20) / 100.0f + 0.05f;
    model = glm::scale(model, glm::vec3(scale));
    GLfloat rotAngle = (rand() % 360);
    model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0.4f, 0.6f, 0.8f));
    modelMatrices[i] = model;
  }
  
  for (GLuint i = 0; i < rock.getMeshes().size(); i++) {
    GLuint VAO = rock.getMeshes()[i].getVAO();
    GLuint buffer;
    glBindVertexArray(VAO);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(3 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    
    glBindVertexArray(0);
  }
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
#if advancedtest != 2
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#elif advancedtest == 2
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif
    
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);
    
#if advancedtest != 10
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
#if advancedtest == 8
    glUniform3f(viewPosLoc, cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
#endif
#endif
#if advancedtest == 13
    modelShader.Use();
    glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(modelProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
#endif
#if advancedtest == 15
    instanceShader.Use();
    glUniformMatrix4fv(glGetUniformLocation(instanceShader.GetProgram(), "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(glGetUniformLocation(instanceShader.GetProgram(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
#endif

#if advancedtest == 1 || advancedtest == 3 || advancedtest == 4 || advancedtest == 6 || advancedtest == 7 || advancedtest == 8 || advancedtest == 9
    shader.Use();
    glBindVertexArray(cubeVAO);
#if advancedtest != 8 && advancedtest != 9
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
#elif advancedtest == 7
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    model.Draw(shader);
#endif
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.01f, -1.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
#if advancedtest != 9
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.01f, 0.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
#elif advancedtest == 9
//    glDrawArrays(GL_POINTS, 0, 36);
    glDrawArrays(GL_TRIANGLES, 0, 36);
#endif
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
#if advancedtest < 7
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindTexture(GL_TEXTURE_2D, planeTexture);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
#endif
    
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
    
#if advancedtest == 7 || advancedtest == 8
    //    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    skyboxShader.Use();
    viewMat = glm::mat4(glm::mat3(cam.getViewMatrix()));
    glUniformMatrix4fv(skyboxViewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(skyboxProjMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
//    glUniform1i(glGetUniformLocation(skyboxShader.GetProgram(), "tex"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    //    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
#endif
    
#if advancedtest == 10
    viewMat = cam.getViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(viewMat));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    glBindVertexArray(cubeVAO);
    redShader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-0.75, 0.75, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(redShader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    greenShader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.75, 0.75, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(greenShader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    blueShader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-0.75, -0.75, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(blueShader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    yellowShader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.75, -0.75, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(yellowShader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
#endif
    
#if advancedtest == 11
    shader.Use();
    glBindVertexArray(pointsVAO);
    glDrawArrays(GL_POINTS, 0, 4);
    glBindVertexArray(0);
#endif
    
#if advancedtest == 12
    shader.Use();
    modelMat = glm::mat4();
    modelMat = glm::scale(modelMat, glm::vec3(0.2f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniform1f(glGetUniformLocation(shader.GetProgram(), "time"), glfwGetTime());
    model.Draw(shader);
#endif
    
#if advancedtest == 13
    modelShader.Use();
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelModelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    model.Draw(modelShader);
    
    shader.Use();
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    model.Draw(shader);
#endif
    
#if advancedtest == 14
    shader.Use();
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindVertexArray(quadVAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
    glBindVertexArray(0);
#endif
    
#if advancedtest == 15
    shader.Use();
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, -5.0f, 0.0f));
    modelMat = glm::scale(modelMat, glm::vec3(0.4));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    planet.Draw(shader);
    
//    for (GLuint i = 0; i < amount; i++) {
//      glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMatrices[i]));
//      rock.Draw(shader);
//    }
    instanceShader.Use();
    glBindTexture(GL_TEXTURE_2D, rock.getTexturesLoaded()[0].id);
    for (GLuint i = 0; i < rock.getMeshes().size(); i++) {
      glBindVertexArray(rock.getMeshes()[i].getVAO());
      glDrawElementsInstanced(GL_TRIANGLES, rock.getMeshes()[i].vertices.size(), GL_UNSIGNED_INT, 0, amount);
      glBindVertexArray(0);
    }
#endif
    
    glfwSwapBuffers(window);
  }

  return 0;
}
