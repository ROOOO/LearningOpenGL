// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ShaderReader.hpp"
#include "CommonSettings.hpp"
#include "TextureReader.hpp"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// test1  VAO and VBO
// test2  VAO, VBO, EBO
// test3  MAX attrib
// test4  vertex shader out, fragment shader in
// test5  uniform
// test6  vertex shader input color
// test7  Shader Class
// test8  Textures
// test9  Double textures
// test10 glm
// test11 glm rotation
// test12 local model view projection clip
// test13 3D cubes
// test14 Camara, Circle move
// test15 Camara, free move

#define test 15

#if test == 15
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat cameraSpeed = 0.05f;
GLboolean keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (action == GLFW_PRESS) {
    keys[key] = true;
  }
  if (action == GLFW_RELEASE) {
    keys[key] = false;
  }
};
void do_movement() {
  cameraSpeed = 5.0f * deltaTime;
  if (keys[GLFW_KEY_W]) {
    cameraPos += cameraSpeed * cameraFront;
  }
  if (keys[GLFW_KEY_S]) {
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (keys[GLFW_KEY_A]) {
    cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
  }
  if (keys[GLFW_KEY_D]) {
    cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
  }
  if (keys[GLFW_KEY_Q]) {
    cameraPos.y -= cameraSpeed;
  }
  if (keys[GLFW_KEY_E]) {
    cameraPos.y += cameraSpeed;
  }
}
GLfloat lastX = 400.0f, lastY = 300.0f;
GLboolean firstMouse = true;
GLfloat pitch = 0.0f, yaw = -90.0f;
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
  
  GLfloat sensitivity = 0.05f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;
  
  yaw += xOffset;
  pitch += yOffset;
  
  pitch = fabs(pitch) > 89.0f ? (pitch > 0 ? 89.0f : -89.0f) : pitch;
  
  glm::vec3 front;
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  cameraFront = glm::normalize(front);
}
GLfloat aspect = 45.0f;
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
  if (aspect >= 1.0f && aspect <= 45.0f) {
    aspect -= yOffset;
  }
  aspect = aspect < 1.0f ? 1.0f : aspect;
  aspect = aspect > 45.0f ? 45.0f : aspect;
}
#endif

int main(){
  CommonSettings Settings;
  GLFWwindow *window = nullptr;
  window = Settings.CreateWindow();
  
#if test == 15
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
#endif

  ////////////////////////////// vertext shader //////////////////////////////
#if test < 7
#if test != 4 && test != 6
  const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "}\0";
#elif test == 6
  const GLchar* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "layout (location = 1) in vec3 color;\n"
  "out vec3 ourColor;\n"
  "void main()\n"
  "{\n"
  "gl_Position = vec4(position, 1.0);\n"
  "ourColor = color;\n"
  "}\0";
#else
  const GLchar* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "out vec4 vertexColor;\n"
  "void main()\n"
  "{\n"
  "gl_Position = vec4(position, 1.0);\n"
  "vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
  "}\0";
#endif
  
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  
  ////////////////////////////// fragment shader //////////////////////////////
#if test < 3
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";
#elif test == 5
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "out vec4 color;\n"
  "uniform vec4 vertexColor;\n"
  "void main()\n"
  "{\n"
  "color = vertexColor;\n"
  "}\0";
#elif test == 6
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "in vec3 ourColor;\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vec4(ourColor, 1.0f);\n"
  "}\0";
#else
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "in vec4 vertexColor;\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vertexColor;\n"
  "}\0";
#endif  
  
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  ////////////////////////////// shader program //////////////////////////////
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  
  glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
#endif
  
#if test == 7
  ShaderReader ShaderReader("/Users/king/git/LearningOpenGL/Files/Getting Start/shader_test7.vs", "/Users/king/git/LearningOpenGL/Files/Getting Start/shader_test7.frag");
#elif test == 8
  ShaderReader ShaderReader("/Users/king/git/LearningOpenGL/Files/Getting Start/shader_test8.vs", "/Users/king/git/LearningOpenGL/Files/Getting Start/shader_test8.frag");
#elif test == 9
  ShaderReader ShaderReader(Settings.CCShadersPath("shader_test9.vs").c_str(), Settings.CCShadersPath("shader_test9.frag").c_str());
#elif test == 11
  ShaderReader ShaderReader(Settings.CCShadersPath("shader_test11.vs").c_str(), Settings.CCShadersPath("shader_test11.frag").c_str());
#elif test == 12
  ShaderReader ShaderReader(Settings.CCShadersPath("shader_test12.vs").c_str(), Settings.CCShadersPath("shader_test12.frag").c_str());
#elif test == 13 || test == 14 || test == 15
  ShaderReader ShaderReader(Settings.CCShadersPath("shader_test13.vs").c_str(), Settings.CCShadersPath("shader_test13.frag").c_str());
#endif
  
  ////////////////////////////// VAO VBO EBO //////////////////////////////
#if test < 6 && test != 2
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };
#elif test == 8 || test == 9
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3,
  };
#elif test == 7
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  };
#elif test == 2
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
  };
  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3,
  };
#elif test == 11 || test == 12
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
  };
  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3,
  };
#elif test == 13 || test == 14 || test == 15
  GLfloat vertices[] = {
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
  };
#endif

  GLuint VBO, VAO, EBO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  
#if test == 1 || test == 4 || test == 5
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#elif test == 6 || test == 7
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#elif test == 8 || test == 9
  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  // 2, 2
  glEnableVertexAttribArray(2);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#elif test == 2
  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#elif test == 11 || test == 12
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#elif test == 13 || test == 14 || test == 15
  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
#endif
  
  ////////////////////////////// output GL_MAX_VERTEX_ATTRIBS //////////////////////////////
#if test == 3
  GLint nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "MAX vertex attribs is " << nrAttributes << std::endl;
#endif
  
  ////////////////////////////// textures //////////////////////////////
#if test == 8
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  int texWidth, texHeight;
  unsigned char* image = SOIL_load_image("/Users/king/git/LearningOpenGL/Files/Getting Start/container.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
#elif test >= 9 && test != 10
  GLuint textures[2];
  TextureReader texR1(Settings.CCResourcesPath("container.jpg").c_str());
  textures[0] = texR1.getTexture();
  TextureReader texR2(Settings.CCResourcesPath("awesomeface.png").c_str());
  textures[1] = texR2.getTexture();
#endif
  
  ////////////////////////////// GLM //////////////////////////////
#if test == 10
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
  vec = trans * vec;
  std::cout << vec.x << vec.y << vec.z << std::endl;
#elif test == 11
  glm::mat4 trans;
  trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
#elif test == 12
  glm::mat4 modelMat;
  modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 viewMat;
  viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -1.5f));
  glm::mat4 projMat;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  projMat = glm::perspective(45.0f,(float)width / height, 0.1f, 100.0f);
#elif test == 13 || test == 14 || test == 15
  glm::mat4 modelMat;
  glm::mat4 viewMat;
#if test == 13 || test == 15
  viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
#elif test == 14
  viewMat = glm::mat4();
  GLfloat radius = 20.0f;
  GLfloat camX = 0;
  GLfloat camZ = 0;
#endif
  glm::mat4 projMat;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  projMat = glm::perspective(glm::radians(45.0f),(float)width / height, 0.1f, 100.0f);
  glEnable(GL_DEPTH_TEST);
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
  
  ////////////////////////////// main loop //////////////////////////////
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
#if test == 1 || test == 4 || test == 6
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#elif test == 2
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#elif test == 5
    glUseProgram(shaderProgram);
    GLfloat timeValue = glfwGetTime();
    GLfloat colorVal = (sin(timeValue) / 2) + 0.5;
    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
    glUniform4f(vertexColorLocation, 0.0f, colorVal, 0.0f, 1.0);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#elif test == 7
    ShaderReader.Use();
    GLfloat timeValue = glfwGetTime();
    GLfloat colorVal = (sin(timeValue) / 2) + 0.5f;
    GLint vertexColorLocation = glGetUniformLocation(ShaderReader.GetProgram(), "ourColor");
    glUniform4f(vertexColorLocation, colorVal, 0.0f, 0.0f, 1.0f);
    ShaderReader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#elif test == 8
    glBindTexture(GL_TEXTURE_2D, texture);
//    glUniform1ui(glGetUniformLocation(ShaderReader.GetProgram(), "ourTexture"), 0);
    ShaderReader.Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
#elif test >= 9 && test != 10
    const char* vars[2] = {
      "ourTexture1", "ourTexture2",
    };
    
    ShaderReader.Use();
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(glGetUniformLocation(ShaderReader.GetProgram(), vars[i]), i);
    }
#if test == 11
    trans = glm::mat4();
    trans = glm::rotate(trans, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "transform"), 1, GL_FALSE, glm::value_ptr(trans));
#elif test == 12
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
#endif
#if test == 11 || test == 12
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
#elif test == 13 || test == 14 || test == 15
    modelMat = glm::mat4();
    modelMat = glm::rotate(modelMat, glm::radians((float)glfwGetTime() * 90.0f), glm::vec3(0.5f, 1.0f, -0.5f));
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
#if test == 14
    camX = sin(glfwGetTime()) * radius;
    camZ = cos(glfwGetTime()) * radius;
    viewMat = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
#endif
#if test == 15
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    do_movement();
    viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projMat = glm::perspective(glm::radians(aspect), (float)width / height, 0.1f, 100.0f);
#endif
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    for (GLuint i = 0; i < 10; i++) {
      modelMat = glm::mat4();
      modelMat = glm::translate(modelMat, cubePositions[i]);
      modelMat = glm::rotate(modelMat, glm::radians((float)glfwGetTime() * -90.0f), glm::vec3(0.5f, 1.0f, -0.5f));
      glUniformMatrix4fv(glGetUniformLocation(ShaderReader.GetProgram(), "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
#endif
#endif
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
	return 0;
}
