//
//  Mesh.cpp
//  Mac
//
//  Created by King on 16/7/8.
//  Copyright © 2016年 King. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;
  this->m_setupMesh();
}

void Mesh::m_setupMesh() {
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);
  
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
  glEnableVertexAttribArray(2);
  
  glBindVertexArray(0);
}

void Mesh::Draw(ShaderReader shader) {
  GLuint diffuseNr = 1;
  GLuint specularNr = 1;
  GLuint reflectionNr = 1;
  for (GLuint i = 0; i < this->textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    stringstream ss;
    string number;
    string name = this->textures[i].type;
    if (name == "texture_diffuse") {
      ss << diffuseNr++;
    } else if (name == "texture_specular") {
      ss << specularNr++;
    } else if (name == "texture_reflection") {
      ss << reflectionNr++;
    }
    number = ss.str();
    glUniform1f(glGetUniformLocation(shader.GetProgram(), ("material." + name + number).c_str()), i);
    glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);
  
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
