// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ShaderReader.hpp"
#include <SOIL.h>

// test1  VAO and VBO
// test2  VAO, VBO, EBO
// test3  MAX attrib
// test4  vertex shader out, fragment shader in
// test5  uniform
// test6  vertex shader input color
// test7  Shader Class
// test8  Textures

#define test8

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glfwSetKeyCallback(window, key_callback);

#if !defined(test7)
#if !defined(test4) && !defined(test6)
  const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "}\0";
#elif defined(test6)
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
  
#if !defined(test4) && !defined(test5) && !defined(test6)
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\0";
#elif defined(test5)
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "out vec4 color;\n"
  "uniform vec4 vertexColor;\n"
  "void main()\n"
  "{\n"
  "color = vertexColor;\n"
  "}\0";
#elif defined(test6)
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
  
  GLuint VBO, VAO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

#if !defined(test6) && !defined(test7) && !defined(test8)
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
  };
#elif defined(test8)
  GLfloat vertices[] = {
    
  };
  GLuint indices[] = {
    
  };
#else
  GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  };
#endif

#if !defined(test2) && !defined(test3) && !defined(test6) && !defined(test7)
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#elif defined(test6) || defined(test7)
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
#endif
#ifdef test2
  GLfloat vertices2[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
  };
  GLuint indices[] = {
    0, 1, 3,
    1, 2, 3,
  };
  
  GLuint EBO;
  glGenBuffers(1, &EBO);
  
  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
#ifdef test3
  GLint nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "MAX vertex attribs is " << nrAttributes << std::endl;
#endif
#ifdef test8
  int texWidth, texHeight;
  unsigned char* image = SOIL_load_image("wall.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
#endif
  
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
#if defined(test1) || defined(test4) || defined(test6)
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#elif defined(test2)
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#elif defined(test5)
    glUseProgram(shaderProgram);
    GLfloat timeValue = glfwGetTime();
    GLfloat colorVal = (sin(timeValue) / 2) + 0.5;
    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
    glUniform4f(vertexColorLocation, 0.0f, colorVal, 0.0f, 1.0);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#elif defined(test7)
    ShaderReader ShaderReader("/Users/king/git/LearningOpenGL/Files/Getting Start/shader.vs", "/Users/king/git/LearningOpenGL/Files/Getting Start/shader.frag");
    ShaderReader.Use();
    GLfloat timeValue = glfwGetTime();
    GLfloat colorVal = (sin(timeValue) / 2) + 0.5f;
    GLint vertexColorLocation = glGetUniformLocation(ShaderReader.GetProgram(), "ourColor");
    glUniform4f(vertexColorLocation, colorVal, 0.0f, 0.0f, 1.0f);
    ShaderReader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
#endif
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
	return 0;
}
