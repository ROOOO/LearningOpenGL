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

glm::mat4 Camera::getViewMatrix() {
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

void Camera::m_updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(this->m_pitch)) * cos(glm::radians(this->m_yaw));
  front.y = sin(glm::radians(this->m_pitch));
  front.z = cos(glm::radians(this->m_pitch)) * sin(glm::radians(this->m_yaw));
  this->m_front = glm::normalize(front);
  this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));
  this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
}