//
//  TextureReader.hpp
//  Mac
//
//  Created by King on 16/6/24.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef TextureReader_hpp
#define TextureReader_hpp

#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <vector>
#include <iostream>

class TextureReader {
  GLuint m_texture;
  
public:
  TextureReader(std::vector<std::string> faces);
  TextureReader(const GLchar* path, GLboolean isAlphaTexture = false, GLboolean isGammaCorrection = false);
  ~TextureReader();
  GLuint getTexture();
  GLuint getCubeMap();
};

#endif /* TextureReader_hpp */
