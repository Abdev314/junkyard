#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Math/Vector3.hpp"
#include "Physics/Force.hpp"
#include "Physics/Torque.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Matrix3.hpp"

class RigidBody {

    private:
        float mass;
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        Quaternion orientation;
        Vector3 angularVelocity;
        Vector3 angularAcceleration;
        Force force;
        Torque torque;
        Matrix3 inertiaTensor;

    public:
        RigidBody(
            float mass,
            Vector3 position,
            Vector3 velocity,
            Vector3 acceleration,
            Quaternion orientation,
            Vector3 angularVelocity,
            Vector3 angularAcceleration,
            Force force,
            Torque torque,
            Matrix3 inertiaTensor
        );

        float getMass() const;
        Vector3 getPosition() const;
        Vector3 getVelocity() const;
        Vector3 getAcceleration() const;
        Quaternion getOrientation() const;
        Vector3 getAngularVelocity() const;
        Vector3 getAngularAcceleration() const;
        Force getForce() const;
        Torque getTorque() const;
        Matrix3 getInertiaTensor() const;

        void ApplyForce(const Force& force);
        void ApplyTorque(const Torque& torque);
        void Update(float deltaTime);
};

#endif