//
//  ShaderReader.cpp
//  Mac
//
//  Created by King on 16/6/18.
//  Copyright © 2016年 King. All rights reserved.
//

#include "ShaderReader.hpp"

ShaderReader::ShaderReader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath) {
  string vertexCodes, fragmentCodes;
  try {
    ifstream vShaderFile(vertexShaderPath), fShaderFile(fragmentShaderPath);
    stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCodes = vShaderStream.str();
    fragmentCodes = fShaderStream.str();
  } catch (exception e) {
    cout << "Read shader files error.\n" << endl;
  }
  
  const GLchar* vShaderCodes = vertexCodes.c_str();
  const GLchar* fShaderCodes = fragmentCodes.c_str();
  GLuint vertexShader, fragmentShader;
  int success;
  GLchar infoLog[512];
  
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCodes, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
    cout << "Compile vertex shader failed\n" << infoLog << endl;
    return;
  }
  
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCodes, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
    cout << "Compile fragment shader failed\n" << infoLog << endl;
    return;
  }
  
  this->m_shaderProgram = glCreateProgram();
  glAttachShader(this->m_shaderProgram, vertexShader);
  glAttachShader(this->m_shaderProgram, fragmentShader);
  glLinkProgram(this->m_shaderProgram);
  glGetProgramiv(this->m_shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->m_shaderProgram, sizeof(infoLog), nullptr, infoLog);
    cout << "Program link failed\n" << infoLog << endl;
    return;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

ShaderReader::ShaderReader(string vertexShaderPath, string fragmentShaderPath, string geometryShaderPath) {
  string vertexCodes, fragmentCodes, geometryCodes;
  try {
    ifstream vShaderFile(vertexShaderPath), fShaderFile(fragmentShaderPath), gShaderFile(geometryShaderPath);
    stringstream vShaderStream, fShaderStream, gShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    gShaderStream << gShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    gShaderFile.close();
    vertexCodes = vShaderStream.str();
    fragmentCodes = fShaderStream.str();
    geometryCodes = gShaderStream.str();
  } catch (exception e) {
    cout << "Read shader files error.\n" << endl;
  }
  
  const GLchar* vShaderCodes = vertexCodes.c_str();
  const GLchar* fShaderCodes = fragmentCodes.c_str();
  const GLchar* gShaderCodes = geometryCodes.c_str();
  GLuint vertexShader, fragmentShader, geometryShader;
  int success;
  GLchar infoLog[512];
  
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCodes, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
    cout << "Compile vertex shader failed\n" << infoLog << endl;
    return;
  }
  
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCodes, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
    cout << "Compile fragment shader failed\n" << infoLog << endl;
    return;
  }
  
  geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(geometryShader, 1, &gShaderCodes, nullptr);
  glCompileShader(geometryShader);
  glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(geometryShader, sizeof(infoLog), nullptr, infoLog);
    cout << "Compile geometry shader failed\n" << infoLog << endl;
    return;
  }
  
  this->m_shaderProgram = glCreateProgram();
  glAttachShader(this->m_shaderProgram, vertexShader);
  glAttachShader(this->m_shaderProgram, fragmentShader);
  glAttachShader(this->m_shaderProgram, geometryShader);
  glLinkProgram(this->m_shaderProgram);
  glGetProgramiv(this->m_shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->m_shaderProgram, sizeof(infoLog), nullptr, infoLog);
    cout << "Program link failed\n" << infoLog << endl;
    return;
  }
  
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(geometryShader);
}

GLuint ShaderReader::GetProgram() {
  return this->m_shaderProgram;
}

void ShaderReader::Use() {
  glUseProgram(this->m_shaderProgram);
}