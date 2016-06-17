#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int t() {
  glfwTerminate();
  return -1;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main() {\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
"}\0";

const GLchar* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 color;\n"
"void main() {\n"
"color = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
"}\n";
const GLchar* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 color;\n"
"void main() {\n"
"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(800, 600, "EX_GS_HT_3", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Create window failed" << std::endl;
    return t();
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW Init failed" << std::endl;
    return t();
  }
  
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  GLint success;
  GLchar logInfo[512];

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(logInfo), nullptr, logInfo);
    std::cout << "Compile vertex shader failed\n" << logInfo << std::endl;
    return t();
  }

  GLuint fragmentShader[2];
  fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader[0], 1, &fragmentShaderSource1, nullptr);
  glCompileShader(fragmentShader[0]);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(logInfo), nullptr, logInfo);
    std::cout << "Compile fragment shader 1 failed\n" << logInfo << std::endl;
    return t();
  }
  fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, nullptr);
  glCompileShader(fragmentShader[1]);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(logInfo), nullptr, logInfo);
    std::cout << "Compile fragment shader 2 failed\n" << logInfo << std::endl;
    return t();
  }

  GLuint shaderProgram[2];
  for (int i = 0; i < 2; i++) {
    shaderProgram[i] = glCreateProgram();
    glAttachShader(shaderProgram[i], vertexShader);
    glAttachShader(shaderProgram[i], fragmentShader[i]);
    glLinkProgram(shaderProgram[i]);
  }

  GLfloat verties[] = {
    1.0f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    -1.0f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  };
  GLint indices[] = {
    0, 1, 4,
    1, 2, 3,
  };

  GLuint VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verties), verties, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram[0]);

    glUseProgram(shaderProgram[1]);

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}