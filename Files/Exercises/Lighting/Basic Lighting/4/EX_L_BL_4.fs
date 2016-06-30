#version 330 core
out vec4 color;

in vec3 ourColor;
uniform vec3 objectColor;

void main() {
  color = vec4(ourColor * objectColor, 1.0f);
}