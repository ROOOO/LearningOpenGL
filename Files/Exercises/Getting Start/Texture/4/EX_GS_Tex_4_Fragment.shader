#version 330 core
out vec4 color;
in vec2 ourTexCoord;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main () {
  color = mix(texture(tex1, vec2(ourTexCoord.x, 1 - ourTexCoord.y)), texture(tex2, vec2(ourTexCoord.x, 1 - ourTexCoord.y)), 0.2f);
}