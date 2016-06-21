#version 330 core
out vec4 color;
in vec2 texCoord;
uniform sampler2D tex1;
uniform sampler2D tex2;
void main () {
  color = mix(texture(tex1, vec2(texCoord.x, 1 - texCoord.y)), texture(tex2, vec2(texCoord.x, 1 - texCoord.y)), 0.3f);
}