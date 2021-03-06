#include "CommonSettings.hpp"

Camera cam(glm::vec3(0.0f, 0.0f, 5.0f));
GLboolean keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED == glfwGetInputMode(window, GLFW_CURSOR) ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
  }
  if (action == GLFW_PRESS) {
    keys[key] = true;
  }
  if (action == GLFW_RELEASE) {
    keys[key] = false;
  }
};
void do_movement() {
  if (keys[GLFW_KEY_LEFT_SHIFT]) {
    deltaTime *= 2;
  }
  if (keys[GLFW_KEY_W]) {
    cam.processKeyBoard(Camera::FORWARD, deltaTime);
  }
  if (keys[GLFW_KEY_S]) {
    cam.processKeyBoard(Camera::BACKWARD, deltaTime);
  }
  if (keys[GLFW_KEY_A]) {
    cam.processKeyBoard(Camera::LEFT, deltaTime);
  }
  if (keys[GLFW_KEY_D]) {
    cam.processKeyBoard(Camera::RIGHT, deltaTime);
  }
  if (keys[GLFW_KEY_Q]) {
    cam.processKeyBoard(Camera::DOWN, deltaTime);
  }
  if (keys[GLFW_KEY_E]) {
    cam.processKeyBoard(Camera::UP, deltaTime);
  }
}

GLfloat lastX = 400.0f, lastY = 300.0f;
GLboolean firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  GLfloat xOffset = xpos - lastX;
  GLfloat yOffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  cam.processMouseMovement(xOffset, yOffset);
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
  cam.processMouseScroll(yOffset);
}

int main(int argc, const char * argv[]) {
  CommonSettings Settings;
  GLFWwindow *window = Settings.CreateWindow();
  if (window == nullptr) {
    std::cout << "Create window failed." << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  GLint width, height;
  glfwGetFramebufferSize(window, &width, &height);

  GLfloat planeVertices[] = {
    // Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
    5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
    -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

    5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
    5.0f, -0.5f, -5.0f, 2.0f, 2.0f
  };
  GLfloat cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top-left
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
    // Right face
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
    // Top face
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f  // bottom-left
  };
  GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // Positions   // TexCoords
    -0.3f, 1.0f, 0.0f, 1.0f,
    0.3f, 1.0f, 1.0f, 1.0f,
    0.3f, 0.7f, 1.0f, 0.0f,

    -0.3f, 1.0f, 0.0f, 1.0f,
    0.3f, 0.7f, 1.0f, 0.0f,
    -0.3f, 0.7f, 0.0f, 0.0f
  };

  GLuint cubeVAO, cubeVBO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLuint planeVAO, planeVBO;
  glGenVertexArrays(1, &planeVAO);
  glGenBuffers(1, &planeVBO);
  glBindVertexArray(planeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GLuint quadVAO, quadVBO;
  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &quadVBO);
  glBindVertexArray(quadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  TextureReader cubeTex(Settings.CCResourcesPath("container.jpg").c_str());
  TextureReader planeTex(Settings.CCResourcesPath("metal.png").c_str());
  GLuint cubeTexture = cubeTex.getTexture();
  GLuint planeTexture = planeTex.getTexture();

#ifdef __APPLE__
  string path = "/Framebuffers/1/";
#else
  string path = "\\Framebuffers\\1\\";
#endif

  ShaderReader shader(Settings.CCExercisesPath(path + "EX_AO_FB_1_cmn.vert").c_str(), Settings.CCExercisesPath(path + "EX_AO_FB_1_cmn.frag").c_str());
  ShaderReader screenShader(Settings.CCExercisesPath(path + "EX_AO_FB_1.vert").c_str(), Settings.CCExercisesPath(path + "EX_AO_FB_1.frag").c_str());

  glm::mat4 modelMat;
  glm::mat4 viewMat;
  glm::mat4 projMat;

  shader.Use();
  GLint modelMatLoc = glGetUniformLocation(shader.GetProgram(), "modelMat");
  GLint viewMatLoc = glGetUniformLocation(shader.GetProgram(), "viewMat");
  GLint projMatLoc = glGetUniformLocation(shader.GetProgram(), "projMat");

  GLuint framebuffer;
  glGenFramebuffers(1, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  GLuint fbTexture;
  glGenTextures(1, &fbTexture);
  glBindTexture(GL_TEXTURE_2D, fbTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbTexture, 0);

  GLuint RBO;
  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Framebuffers failed.\n" << std::endl;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    do_movement();

    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.setYaw(cam.getYaw() + 180.0f);
    cam.processMouseMovement(0, 0, false);
    viewMat = cam.getViewMatrix();
    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);

    shader.Use();
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.01f, -1.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.01f, 0.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindTexture(GL_TEXTURE_2D, planeTexture);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    cam.setYaw(cam.getYaw() - 180.0f);
//    cam.setPitch(cam.getPitch() - 180.0f);
    cam.processMouseMovement(0, 0);

    viewMat = cam.getViewMatrix();
//    projMat = glm::perspective(cam.getZoom(), (GLfloat)width / height, 0.1f, 100.0f);
    
    shader.Use();
    glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
//    glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
    
    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(-1.0f, 0.01f, -1.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(2.0f, 0.01f, 0.0f));
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    modelMat = glm::mat4();
    glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindTexture(GL_TEXTURE_2D, planeTexture);
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDisable(GL_DEPTH_TEST);
    screenShader.Use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, fbTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  return 0;
}
