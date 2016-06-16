//
//  main.cpp
//  Mac
//
//  Created by King on 16/6/16.
//  Copyright © 2016年 King. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

const GLchar* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "void main() {\n"
  "gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n" // 1.0f
  "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
  "out vec4 color;\n"
  "void main() {\n"
  "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
  GLFWwindow* window = glfwCreateWindow(800, 600, "EX_GS_HT_2", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Create window failed" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  
  glfwSetKeyCallback(window, key_callback);
  
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW INIT failed" << std::endl;
    glfwTerminate();
    return -1;
  }
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  
  GLint success;
  GLchar infoLog[512];
  
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
    std::cout << "Compile vertex shader failed\n" << infoLog << std::endl;
    glfwTerminate();
    return -1;
  }
  
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
    std::cout << "Compile fragment shader failed\n" << infoLog << std::endl;
    glfwTerminate();
    return -1;
  }
  
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
    std::cout << "Failed to Link Shaders\n" << infoLog << std::endl;
    glfwTerminate();
    return -1;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  GLfloat vertices1[] = {
    0.0f, -0.5f, 0.0f,
    -1.0f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
  };
  GLfloat vertices2[] = {
    1.0f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };
  
  GLuint VBO[2], VAO[2];
  glGenBuffers(2, VBO);
  glGenVertexArrays(2, VAO);
  
  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);  // size
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //size
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
  }
  
  glDeleteBuffers(sizeof(VBO), VBO);
  glDeleteVertexArrays(sizeof(VAO), VAO);
  
  glfwTerminate();
  return -1;
}