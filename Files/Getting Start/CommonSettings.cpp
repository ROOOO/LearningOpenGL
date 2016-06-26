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
  m_ShadersPath = "/Users/king/git/LearningOpenGL/Files/Getting Start/Shaders/";
  m_ResourcesPath = "/Users/king/git/LearningOpenGL/Files/Getting Start/Resources/";
  m_FilesPath = "/Users/king/git/LearningOpenGL/Files/Getting Start/";
  m_ExercisesPath = "/Users/king/git/LearningOpenGL/Files/Exercises/Getting Start/";
#else
  m_ShadersPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Shaders\\";
  m_ResourcesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Resources\\";
  m_FilesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\";
  m_ExercisesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Exercises\\Getting Start\\";
#endif
}

CommonSettings::~CommonSettings() {
}

void CommonSettings::m_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

GLFWwindow *CommonSettings::CreateWindow(string titleName) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
  GLFWwindow* window = glfwCreateWindow(800, 600, titleName.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, m_key_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
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

string CommonSettings::CCShadersPath(string str) {
  return m_ShadersPath + str;
}

string CommonSettings::CCResourcesPath(string str) {
  return m_ResourcesPath + str;
}

string CommonSettings::CCFilesPath(string str) {
  return m_FilesPath + str;
}
string CommonSettings::CCExercisesPath(string str) {
  return m_ExercisesPath + str;
}
