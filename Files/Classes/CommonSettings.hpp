//
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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"
#include "ShaderReader.hpp"
#include "TextureReader.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include <vector>
#include <map>

using namespace std;

class CommonSettings {
  
  string m_ShadersPath = "";
  string m_ResourcesPath = "";
  string m_FilesPath = "";
  string m_ExercisesPath = "";
  string m_ModelsPath = "";
#ifdef __APPLE__
  string m_ProjectPath = "/Users/king/git/LearningOpenGL/Files/";
#else
  string m_ProjectPath = "D:\\Projects\\OpenGL\\LearningOpenGL\\Files\\";
#endif
  
  static void m_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
  CommonSettings();
  ~CommonSettings();
  GLFWwindow *CreateWindow(string titleName = "Learning OpenGL");
  string CCFilesPath(string str);
  string CCExercisesPath(string str);
  string CCResourcesPath(string str);
  string CCShadersPath(string str);
  string CCModelsPath(string str);
};

#endif /* CommonSettings_hpp */
