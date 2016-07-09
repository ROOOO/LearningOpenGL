//
//  Model.hpp
//  Mac
//
//  Created by King on 16/7/8.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.hpp"
#include <SOIL/SOIL.h>

class Model {
  vector<Texture> m_texturesLoaded;
  vector<Mesh> m_meshes;
  string m_directory;
  
  void m_loadModel(string path);
  void m_processNode(aiNode *node, const aiScene *scene);
  Mesh m_processMesh(aiMesh *mesh, const aiScene *scene);
  vector<Texture> m_loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
  
  GLuint m_textureFromFile(const char* path, string directory);
  
public:
  Model(const GLchar *path);
  void Draw(ShaderReader shader);
  
};

#endif /* Model_hpp */
