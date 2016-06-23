#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#ifdef __APPLE__
#include "CommonSettings.hpp"
#else
#include "../../../../Getting Start/CommonSettings.hpp"
#endif
#include "ShaderReader.hpp"
#include <SOIL/SOIL.h>

GLfloat offset = 0.0f;
GLfloat trans = 0.2f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    offset += 0.1f;
  } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    offset -= 0.1f;
  } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    trans = 0.2f;
  } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    trans = 0.0f;
  }
}

int main() {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("EX_GS_Tex_4");
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  
#ifdef __APPLE__
  string path = "/Texture/4/";
#else
  string path = "\\Texture\\4\\";
#endif
  
  ShaderReader shader(Settings.CCExercisesPath(path + "EX_GS_Tex_4_Vertex.shader").c_str(), Settings.CCExercisesPath(path + "EX_GS_Tex_4_Fragment.shader").c_str());

  GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
  };
  GLint indices[] = {
    0, 1, 2,
    0, 2, 3,
  };
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);

  unsigned char* images[2];
  int texWidth[2], texHeight[2];
  images[0] = SOIL_load_image(Settings.CCResourcesPath("container.jpg").c_str(), &texWidth[0], &texHeight[0], 0, SOIL_LOAD_RGB);
  images[1] = SOIL_load_image(Settings.CCResourcesPath("awesomeface.png").c_str(), &texWidth[1], &texHeight[1], 0, SOIL_LOAD_RGB);

  GLuint textures[2];
  glGenTextures(2, textures);
  for (int i = 0; i < 2; i++) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth[i], texHeight[i], 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]);

    SOIL_free_image_data(images[i]);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  const GLchar* names[] = {
    "tex1", "tex2",
  };

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(glGetUniformLocation(shader.GetProgram(), names[i]), i);
    }

    glUniform1f(glGetUniformLocation(shader.GetProgram(), "offset"), offset);
    glUniform1f(glGetUniformLocation(shader.GetProgram(), "transparent"), trans);

    shader.Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  
  glfwTerminate();
  return -1;
}