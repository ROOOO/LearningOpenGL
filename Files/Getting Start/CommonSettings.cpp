//
//  CommonSettings.cpp
//  Mac
//
//  Created by King on 16/6/20.
//  Copyright © 2016年 King. All rights reserved.
//

#include "CommonSettings.hpp"

CommonSettings::CommonSettings() {
#ifdef __APPLE__
  m_ShadersFolder = "/Users/king/git/LearningOpenGL/Files/Getting Start/Shaders/";
  m_ResourcesFolder = "/Users/king/git/LearningOpenGL/Files/Getting Start/Resources/";
#else
  m_ShadersFolder = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Shaders\\";
  m_ResourcesFolder = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Resources\\";
#endif
}

CommonSettings::~CommonSettings() {
}

void CommonSettings::m_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow *CommonSettings::CreateWindow(GLFWwindow *window, string titleName) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
  window = glfwCreateWindow(800, 600, titleName.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, m_key_callback);
  
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "GLEW init failed." << std::endl;
    glfwTerminate();
    return nullptr;
  }
  
  int viewWidth, viewHeight;
  glfwGetFramebufferSize(window, &viewWidth, &viewHeight);
  glViewport(0, 0, viewWidth, viewHeight);
  
  return window;
}

const GLchar* CommonSettings::CCResourcesFolder(string str) {
  const GLchar* dst = (m_ResourcesFolder + str).c_str();
  return dst;
}

const GLchar* CommonSettings::CCShadersFolder(string str) {
  const GLchar* dst = (m_ShadersFolder + str).c_str();
  return dst;
}

string CommonSettings::GetResourcesFolder() {
  return m_ResourcesFolder;
}
string CommonSettings::GetShadersFolder() {
  return m_ShadersFolder;
}
