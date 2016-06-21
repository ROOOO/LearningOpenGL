#version 330 core
out vec4 color;
in vec3 ourColor;
in vec2 ourTexCoord;
uniform sampler2D tex1;
uniform sampler2D tex2;
void main () {
//  color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  color = mix(texture(tex1, ourTexCoord), texture(tex2, vec2(ourTexCoord.x, 1 - ourTexCoord.y)), 0.3f);
}