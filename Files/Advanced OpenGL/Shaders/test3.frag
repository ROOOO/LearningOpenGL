#version 330 core
out vec4 color;
in vec2 TexCoords;
uniform sampler2D tex;
void main() {
  vec4 texColor = texture(tex, TexCoords);
  if (texColor.a < 0.1) {
    discard;
  }
  color = texColor;
}