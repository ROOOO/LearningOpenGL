//
//  Mesh.hpp
//  Mac
//
//  Created by King on 16/7/8.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>

#include "ShaderReader.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};
struct Texture {
  GLuint id;
  string type;
  aiString path;
};

class Mesh {
  GLuint VAO, VBO, EBO;
  void m_setupMesh();
  
public:
  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;
  Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
  void Draw(ShaderReader shader);
  GLuint getVAO();
};


#endif /* Mesh_hpp */
