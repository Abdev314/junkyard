#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

    private:
        // Camera position and orientation
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        // Camera rotation
        float yaw;
        float pitch;

        // Perspective projection settings
        float fieldOfView;
        float aspectRatio;
        float nearPlane;
        float farPlane;

        void UpdateCameraVectors();
            

    public:
        Camera(
            glm::vec3 position,
            glm::vec3 worldUp,
            float yaw,
            float pitch,
            float fieldOfView,
            float aspectRatio,
            float nearPlane,
            float farPlane
        );

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        void SetAspectRatio(float aspectRatio);
        void Move(glm::vec3 movement);
        void Rotate(float yawOffset, float pitchOffset);
        void SetFieldOfView(float fieldOfView);
};

#endif