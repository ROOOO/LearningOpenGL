#version 330 core

out vec4 color;

out VS_OUT {
  vec3 normal;
  vec3 fragPos;
  vec2 texCoords;
} fs_in;

uniform vec3 lightPos[4];
uniform vec3 lightColor[4];
uniform vec3 viewPos;
uniform bool gamma;

void main() {
  
}
