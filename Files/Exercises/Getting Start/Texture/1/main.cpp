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

int main() {
  CommonSettings Settings;
  
  GLFWwindow *window = Settings.CreateWindow("EX_GS_Tex_1");
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    return -1;
  }
  
#ifdef __APPLE__
  string path = "/Texture/1/";
#else
  string path = "\\Texture\\1\\";
#endif
  
  ShaderReader shader((Settings.GetExercisesPath() + path + "EX_GS_Tex_1_Vertex.shader").c_str(), (Settings.GetExercisesPath() + path + "EX_GS_Tex_1_Fragment.shader").c_str());

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

  GLuint VAO, VBO, EBO;
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    glGenerateMipmap(GL_TEXTURE_2D);
    
    SOIL_free_image_data(images[i]);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    const char* tex[] = {
      "tex1", "tex2",
    };
    for (int i = 0; i < 2; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, textures[i]);
      glUniform1i(glGetUniformLocation(shader.GetProgram(), tex[i]), i);
    }
    shader.Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  glBindVertexArray(0);
  
  glfwTerminate();  
  return -1;
}
