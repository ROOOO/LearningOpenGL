//
//  Camera.hpp
//  Mac
//
//  Created by King on 16/6/26.
//  Copyright © 2016年 King. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 WORLDUP = glm::vec3(0.0f, 1.0f, 0.0f);
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera {
  glm::vec3 m_position;
  glm::vec3 m_worldUp;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  GLfloat m_movementSpeed;
  GLfloat m_mouseSensitivity;
  GLfloat m_zoom;
  GLboolean m_isFPS = false;
  
  void m_updateCameraVectors();
  
public:
  GLfloat m_yaw;
  GLfloat m_pitch;
  enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
  };
  Camera(glm::vec3 position = POSITION, glm::vec3 up = WORLDUP, GLfloat yaw = YAW, GLfloat pitch = PITCH);
  ~Camera();
  glm::mat4 getViewMatrix();
  void processKeyBoard(Camera_Movement direction, GLfloat deltaTime);
  void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
  void processMouseScroll(GLfloat yOffset);
  GLfloat getZoom();
  void setFPS(GLboolean b);
  glm::vec3 getPosition();
  glm::vec3 getDirection();
  glm::mat4 lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
  void setYaw(GLfloat yaw);
  GLfloat getYaw();
  void setPitch(GLfloat pitch);
  GLfloat getPitch();
};

#endif /* Camera_hpp */
