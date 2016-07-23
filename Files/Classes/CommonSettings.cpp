//
//  CommonSettings.cpp
//  Mac
//
//  Created by King on 16/6/20.
//  Copyright © 2016年 King. All rights reserved.
//

#include "CommonSettings.hpp"

#define test 4

CommonSettings::CommonSettings() {
#ifdef __APPLE__
#if test == 1
  m_ShadersPath = "Getting Start/Shaders/";
  m_ResourcesPath = "Getting Start/Resources/";
  m_FilesPath = "Getting Start/";
  m_ExercisesPath = "Exercises/Getting Start/";
#elif test == 2
  m_ShadersPath = "Lighting/Shaders/";
  m_ResourcesPath = "Lighting/Resources/";
  m_FilesPath = "Lighting/";
  m_ExercisesPath = "Exercises/Lighting/";
#elif test == 3
  m_ShadersPath = "Model Loading/Shaders/";
  m_ResourcesPath = "Model Loading/Resources/";
  m_FilesPath = "Model Loading/";
  m_ExercisesPath = "Exercises/Model Loading/";
  m_ModelsPath = "Model Loading/Models/";
#elif test == 4
  m_ShadersPath = "Advanced OpenGL/Shaders/";
  m_ResourcesPath = "Advanced OpenGL/Resources/";
  m_FilesPath = "Advanced OpenGL/";
  m_ExercisesPath = "Exercises/Advanced OpenGL/";
  m_ModelsPath = "Model Loading/Models/";
#endif
#else
#if test == 1
  m_ShadersPath = "Getting Start\\Shaders\\";
  m_ResourcesPath = "Getting Start\\Resources\\";
  m_FilesPath = "Getting Start\\";
  m_ExercisesPath = "Exercises\\Getting Start\\";
#elif test == 2
  m_ShadersPath = "Lighting\\Shaders\\";
  m_ResourcesPath = "Lighting\\Resources\\";
  m_FilesPath = "Lighting\\";
  m_ExercisesPath = "Exercises\\Lighting\\";
#elif test == 3
  m_ShadersPath = "Model Loading\\Shaders\\";
  m_ResourcesPath = "Model Loading\\Resources\\";
  m_FilesPath = "Model Loading\\";
  m_ExercisesPath = "Exercises\\Model Loading\\";
  m_ModelsPath = "Model Loading\\Models\\";
#elif test == 4
  m_ShadersPath = "Advanced OpenGL\\Shaders\\";
  m_ResourcesPath = "Advanced OpenGL\\Resources\\";
  m_FilesPath = "Advanced OpenGL\\";
  m_ExercisesPath = "Exercises\\Advanced OpenGL\\";
  m_ModelsPath = "Model Loading\\Models\\";
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
  glfwWindowHint(GLFW_SAMPLES, 4);
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
  return m_ProjectPath + m_ShadersPath + str;
}

string CommonSettings::CCResourcesPath(string str) {
  return m_ProjectPath + m_ResourcesPath + str;
}

string CommonSettings::CCFilesPath(string str) {
  return m_ProjectPath + m_FilesPath + str;
}
string CommonSettings::CCExercisesPath(string str) {
  return m_ProjectPath + m_ExercisesPath + str;
}
string CommonSettings::CCModelsPath(string str) {
  return m_ProjectPath + m_ModelsPath + str;
}
