//
//  TextureReader.cpp
//  Mac
//
//  Created by King on 16/6/24.
//  Copyright © 2016年 King. All rights reserved.
//

#include "TextureReader.hpp"

TextureReader::TextureReader(const GLchar* path, GLboolean isAlphaTexture) {
  int width, height;
  unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
  
  glGenTextures(1, &m_texture);
  
  glBindTexture(GL_TEXTURE_2D, m_texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, isAlphaTexture ? GL_CLAMP_TO_EDGE : GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, isAlphaTexture ? GL_CLAMP_TO_EDGE : GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(m_texture);
  
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);
}

TextureReader::~TextureReader() {
  
}

GLuint TextureReader::getTexture() {
  return this->m_texture;
}