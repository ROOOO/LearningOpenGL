#version 330 core
out vec4 color;
in vec2 TexCoords;
uniform sampler2D tex;
void main() {
  color = vec4(vec3(1.0 - texture(tex, TexCoords)), 1.0f);
}