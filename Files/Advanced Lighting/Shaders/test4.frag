#version 330 core
out vec4 color;

in VS_OUT {
  vec2 texCoords;
} fs_in;

uniform sampler2D tex;

void main() {
  float depthValue = texture(tex, fs_in.texCoords).r;
  color = vec4(vec3(depthValue), 1.0f);
//  color = vec4(1.0f);
}