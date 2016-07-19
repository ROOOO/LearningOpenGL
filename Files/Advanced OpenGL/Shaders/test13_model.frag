#version 330 core
out vec4 color;
in VS_OUT {
  vec2 texCoords;
} fs_in;
uniform sampler2D tex;
void main() {
  color = vec4(texture(tex, fs_in.texCoords));
}
