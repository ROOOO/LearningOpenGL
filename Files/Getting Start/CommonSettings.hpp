//
//  CommonSettings.hpp
//  Mac
//
//  Created by King on 16/6/20.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef CommonSettings_hpp
#define CommonSettings_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class CommonSettings {
  
  string m_ShadersFolder = "";
  string m_ResourcesFolder = "";
  string m_FilesFolder = "";
  string m_ExercisesFolder = "";
  
  static void m_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
  CommonSettings();
  ~CommonSettings();
  GLFWwindow *CreateWindow(GLFWwindow *window, string titleName = "Learning OpenGL");
  string GetResourcesFolder();
  string GetShadersFolder();
  string GetFilesFolder();
  string GetExercisesFolder();
  const GLchar* CCResourcesFolder(string str);
  const GLchar* CCShadersFolder(string str);
};

#endif /* CommonSettings_hpp */
