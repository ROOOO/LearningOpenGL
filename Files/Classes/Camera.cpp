//
//  Camera.cpp
//  Mac
//
//  Created by King on 16/6/26.
//  Copyright © 2016年 King. All rights reserved.
//

#include "Camera.hpp"
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) {
  this->m_position = position;
  this->m_worldUp = up;
  this->m_yaw = yaw;
  this->m_pitch = pitch;
  this->m_movementSpeed = SPEED;
  this->m_mouseSensitivity = SENSITIVITY;
  this->m_zoom = ZOOM;
  this->m_updateCameraVectors();
}

Camera::~Camera() {
  
}

glm::mat4 Camera::lookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
  glm::vec3 D = glm::normalize(glm::vec3(position - target));
  glm::vec3 R = glm::normalize(glm::cross(worldUp, D));
  glm::vec3 U = glm::normalize(glm::cross(D, R));
  
  glm::mat4 m1;
  m1[0][0] = R.x;
  m1[0][1] = U.x;
  m1[0][2] = D.x;
  m1[1][0] = R.y;
  m1[1][1] = U.y;
  m1[1][2] = D.y;
  m1[2][0] = R.z;
  m1[2][1] = U.z;
  m1[2][2] = D.z;
  glm::mat4 m2;
  m2[3][0] = -position.x;
  m2[3][1] = -position.y;
  m2[3][2] = -position.z;
  return m1 * m2;
}

glm::mat4 Camera::getViewMatrix() {
//  return this->lookAt(this->m_position, this->m_front + this->m_position, this->m_up);
  return glm::lookAt(this->m_position, this->m_front + this->m_position, this->m_up);
}

void Camera::processKeyBoard(Camera::Camera_Movement direction, GLfloat deltaTime) {
  GLfloat velocity = this->m_movementSpeed * deltaTime;
  if (direction == FORWARD) {
    this->m_position += this->m_front * velocity;
  } else if (direction == BACKWARD) {
    this->m_position -= this->m_front * velocity;
  } else if (direction == LEFT) {
    this->m_position -= this->m_right * velocity;
  } else if (direction == RIGHT) {
    this->m_position += this->m_right * velocity;
  } else if (direction == UP) {
    this->m_position.y += velocity;
  } else if (direction == DOWN) {
    this->m_position.y -= velocity;
  }
  if (this->m_isFPS) {
    this->m_position.y = 0;
  }
  std::cout << "position: " << m_position.x << "  " << m_position.y << "  " << m_position.z << std::endl;
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
  xOffset *= this->m_mouseSensitivity;
  yOffset *= this->m_mouseSensitivity;
  
  this->m_yaw += xOffset;
  this->m_pitch += yOffset;
  
  if (constrainPitch) {
    this->m_pitch = fabs(this->m_pitch) > 89.0 ? (this->m_pitch > 0 ? 89.0f : -89.0f) : this->m_pitch;
  }
  
  this->m_updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yOffset) {
  GLfloat min = 1.0f, max = 90.0f;
  if (this->m_zoom >= min && this->m_zoom <= max) {
    this->m_zoom -= yOffset;
  }
  if (this->m_zoom < min) {
    this->m_zoom = min;
  }
  if (this->m_zoom > max) {
    this->m_zoom = max;
  }
}

GLfloat Camera::getZoom() {
  return m_zoom;
}

void Camera::setFPS(GLboolean b) {
  this->m_isFPS = b;
}

glm::vec3 Camera::getPosition() {
  return this->m_position;
}

void Camera::m_updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(this->m_pitch)) * cos(glm::radians(this->m_yaw));
  front.y = sin(glm::radians(this->m_pitch));
  front.z = cos(glm::radians(this->m_pitch)) * sin(glm::radians(this->m_yaw));
  this->m_front = glm::normalize(front);
  this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));
  this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
  std::cout << "front:  " << m_front.x << " " << m_front.y << " " << m_front.z << std::endl;
}