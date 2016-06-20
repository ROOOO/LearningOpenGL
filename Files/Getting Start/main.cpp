// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "ShaderReader.hpp"
#include <SOIL/SOIL.h>

// test1  VAO and VBO
// test2  VAO, VBO, EBO
// test3  MAX attrib
// test4  vertex shader out, fragment shader in
// test5  uniform
// test6  vertex shader input color
// test7  Shader Class
// test8  Textures
// test9  Double textures

#define test 9

#ifdef __APPLE__
const GLchar* ShadersFolder = "/Users/king/git/LearningOpenGL/Files/Getting Start/";
const GLchar* ResourcesFolder = "/Users/king/git/LearningOpenGL/Files/Getting Start/";
#else
string ShadersFolder = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Shaders\\";
string ResourcesFolder = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Resources\\";
#endif

#include <iostream>

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
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
  
  int widthViewPort, heightViewPort;
  glfwGetFramebufferSize(window, &widthViewPort, &heightViewPort);
  glViewport(0, 0, widthViewPort, heightViewPort);

  glfwSetKeyCallback(window, key_callback);

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
  ShaderReader ShaderReader((ShadersFolder + "shader_test9.vs").c_str(), (ShadersFolder + "shader_test9.frag").c_str());
#endif
  
  ////////////////////////////// VAO VBO EBO //////////////////////////////
#if test < 6
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
#elif test == 9
  unsigned char* images[2];
  int texWidth[2], texHeight[2];
  // awesomeface.png
  // container.jpg
  images[0] = SOIL_load_image((ResourcesFolder + "container.jpg").c_str(), &texWidth[0], &texHeight[0], 0, SOIL_LOAD_RGB);
  images[1] = SOIL_load_image((ResourcesFolder + "awesomeface.png").c_str(), &texWidth[1], &texHeight[1], 0, SOIL_LOAD_RGB);
  
  GLuint textures[2];
  glGenTextures(2, textures);
  
  for (int i = 0; i < 2; i++) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth[i], texHeight[i], 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    SOIL_free_image_data(images[i]);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

#endif
  
  ////////////////////////////// main loop //////////////////////////////
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  
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
#elif test == 9
    const char* vars[2] = {
      "ourTexture1", "ourTexture2",
    };
//    glBindTexture(GL_TEXTURE_2D, textures[0]);
    ShaderReader.Use();
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(glGetUniformLocation(ShaderReader.GetProgram(), vars[i]), i);
    }
    
    ShaderReader.Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
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
