#include "Rendering/Camera.hpp"
#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(
    glm::vec3 position,
    glm::vec3 worldUp,
    float yaw,
    float pitch,
    float fieldOfView,
    float aspectRatio,
    float nearPlane,
    float farPlane
)
    : position(position),
      worldUp(worldUp),
      yaw(yaw),
      pitch(pitch),
      fieldOfView(fieldOfView),
      aspectRatio(aspectRatio),
      nearPlane(nearPlane),
      farPlane(farPlane)
{
    UpdateCameraVectors();
}


glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(position, position + front, up); }

glm::mat4 Camera::GetProjectionMatrix() const { return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane); }

void Camera::SetAspectRatio(float newAspectRatio) { aspectRatio = newAspectRatio; }

void Camera::Move(glm::vec3 movement) { position += movement; }

void Camera::Rotate(float yawOffset, float pitchOffset) { yaw += yawOffset; pitch += pitchOffset; pitch = std::clamp(pitch, -89.0f, 89.0f); UpdateCameraVectors(); }

void Camera::SetFieldOfView(float newFieldOfView) { fieldOfView = std::clamp(newFieldOfView, 1.0f, 90.0f); }

void Camera::UpdateCameraVectors() {
    glm::vec3 newFront;

    newFront.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    newFront.y = std::sin(glm::radians(pitch));
    newFront.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}