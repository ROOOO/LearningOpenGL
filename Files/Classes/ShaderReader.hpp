//
//  ShaderReader.hpp
//  Mac
//
//  Created by King on 16/6/18.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef ShaderReader_hpp
#define ShaderReader_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class ShaderReader {
  GLuint m_shaderProgram;
  
public:
  ShaderReader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
  ShaderReader(string vertexShaderPath, string fragmentShaderPath, string geometryShaderPath);
  GLuint GetProgram();
  void Use();
};

#endif /* ShaderReader_hpp */
