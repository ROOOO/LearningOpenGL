#version 330 core
uniform float offset;
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
out vec2 ourTexCoord;
void main() {
  if (position.x > 0) {
    if (position.y > 0) {
	  gl_Position = vec4(position.x + offset, position.y + offset, position.z, 1.0f);
	} else {
	  gl_Position = vec4(position.x + offset, position.y - offset, position.z, 1.0f);
	}
  } else {
    if (position.y > 0) {
	  gl_Position = vec4(position.x - offset, position.y + offset, position.z, 1.0f);
	} else {
	  gl_Position = vec4(position.x - offset, position.y - offset, position.z, 1.0f);
	}
  }
  ourTexCoord = texCoord;
}