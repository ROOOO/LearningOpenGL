//
//  Model.cpp
//  Mac
//
//  Created by King on 16/7/8.
//  Copyright © 2016年 King. All rights reserved.
//

#include "Model.hpp"

Model::Model(const GLchar *path) {
  this->m_loadModel(path);
}

void Model::Draw(ShaderReader shader) {
  for (GLuint i = 0; i < this->m_meshes.size(); i++) {
    this->m_meshes[i].Draw(shader);
  }
}

void Model::m_loadModel(string path) {
  Assimp::Importer import;
  const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    return;
  }
  this->m_directory = path.substr(0, path.find_last_of('/'));
  this->m_processNode(scene->mRootNode, scene);
}

void Model::m_processNode(aiNode *node, const aiScene *scene) {
  for (GLuint i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    this->m_meshes.push_back(this->m_processMesh(mesh, scene));
  }
  for (GLuint i = 0; i < node->mNumChildren; i++) {
    this->m_processNode(node->mChildren[i], scene);
  }
}

Mesh Model::m_processMesh(aiMesh *mesh, const aiScene *scene) {
  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;
  
  std::cout << mesh->mNumVertices << std::endl;
  for (GLuint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    
    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;
    
    if (!mesh->mNormals) {
      vertex.Normal = glm::vec3(0.0f);
    } else {
    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    vertex.Normal = vector;
    }
    
    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TexCoords = vec;
    } else {
      vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    }
    
    vertices.push_back(vertex);
  }
  
  for (GLuint i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (GLuint j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }
  
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = this->m_loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = this->m_loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    vector<Texture> reflectionMaps = this->m_loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_reflection");
    textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());
  }
  
  return Mesh(vertices, indices, textures);
}

vector<Texture> Model::m_loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName) {
  vector<Texture> textures;
  
  for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    GLboolean skip = false;
    for (GLuint j = 0; j < this->m_texturesLoaded.size(); j++) {
      if (m_texturesLoaded[j].path == str) {
        skip = true;
        textures.push_back(m_texturesLoaded[j]);
        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.id = this->m_textureFromFile(str.C_Str(), this->m_directory);
      texture.type = typeName;
      texture.path = str;
      textures.push_back(texture);
      m_texturesLoaded.push_back(texture);
    }
  }
  
  return textures;
}

GLuint Model::m_textureFromFile(const char *path, string directory) {
  string filename = string(path);
  filename = directory + "/" + filename;
  
  GLuint textureID;
  glGenTextures(1, &textureID);
  int width, height;
  unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(image);
  
  return textureID;
}

vector<Mesh> Model::getMeshes() {
  return this->m_meshes;
}

vector<Texture> Model::getTexturesLoaded() {
  return this->m_texturesLoaded;
}
