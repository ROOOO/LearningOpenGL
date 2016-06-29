//
//  CommonSettings.cpp
//  Mac
//
//  Created by King on 16/6/20.
//  Copyright © 2016年 King. All rights reserved.
//

#include "CommonSettings.hpp"

#define test 2

CommonSettings::CommonSettings() {
#ifdef __APPLE__
#if test == 1
  m_ShadersPath = "/Users/king/git/LearningOpenGL/Files/Getting Start/Shaders/";
  m_ResourcesPath = "/Users/king/git/LearningOpenGL/Files/Getting Start/Resources/";
  m_FilesPath = "/Users/king/git/LearningOpenGL/Files/Getting Start/";
  m_ExercisesPath = "/Users/king/git/LearningOpenGL/Files/Exercises/Getting Start/";
#elif test == 2
  m_ShadersPath = "/Users/king/git/LearningOpenGL/Files/Lighting/Shaders/";
  m_ResourcesPath = "/Users/king/git/LearningOpenGL/Files/Lighting/Resources/";
  m_FilesPath = "/Users/king/git/LearningOpenGL/Files/Lighting/";
  m_ExercisesPath = "/Users/king/git/LearningOpenGL/Files/Exercises/Lighting/";
#endif
#else
#if test == 1
  m_ShadersPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Shaders\\";
  m_ResourcesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\Resources\\";
  m_FilesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Getting Start\\";
  m_ExercisesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Exercises\\Getting Start\\";
#elif test == 2
  m_ShadersPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Lighting\\Shaders\\";
  m_ResourcesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Lighting\\Resources\\";
  m_FilesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Lighting\\";
  m_ExercisesPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\Exercises\\Lighting\\";
#endif
#endif
}

CommonSettings::~CommonSettings() {
}

void CommonSettings::m_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
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
  
  glEnable(GL_DEPTH_TEST);
  
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
