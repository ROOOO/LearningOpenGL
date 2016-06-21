﻿//
//  CommonSettings.hpp
//  Mac
//
//  Created by King on 16/6/20.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef CommonSettings_hpp
#define CommonSettings_hpp

#define GLEW_STATIC
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class CommonSettings {
  
  string m_ShadersPath = "";
  string m_ResourcesPath = "";
  string m_FilesPath = "";
  string m_ExercisesPath = "";
  
  static void m_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
  CommonSettings();
  ~CommonSettings();
  GLFWwindow *CreateWindow(string titleName = "Learning OpenGL");
  string GetResourcesPath();
  string GetShadersPath();
  string GetFilesPath();
  string GetExercisesPath();
  string CCResourcesPath(string str);
  string CCShadersPath(string str);
};

#endif /* CommonSettings_hpp */
