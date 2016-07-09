#version 330 core

out vec4 color;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform sampler2D texture_diffuse1;

void main() {
  color = vec4(texture(texture_diffuse1, TexCoords));
}