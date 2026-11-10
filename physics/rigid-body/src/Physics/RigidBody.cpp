#include "Physics/RigidBody.hpp"

RigidBody::RigidBody(
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
)
    : mass(mass),
      position(position),
      velocity(velocity),
      acceleration(acceleration),
      orientation(orientation),
      angularVelocity(angularVelocity),
      angularAcceleration(angularAcceleration),
      force(force),
      torque(torque),
      inertiaTensor(inertiaTensor) {}

float RigidBody::getMass() const { return mass; }
Vector3 RigidBody::getPosition() const { return position; }
Vector3 RigidBody::getVelocity() const { return velocity; }
Vector3 RigidBody::getAcceleration() const { return acceleration; }
Quaternion RigidBody::getOrientation() const { return orientation; }
Vector3 RigidBody::getAngularVelocity() const { return angularVelocity; }
Vector3 RigidBody::getAngularAcceleration() const { return angularAcceleration; }
Force RigidBody::getForce() const { return force; }
Torque RigidBody::getTorque() const { return torque; }
Matrix3 RigidBody::getInertiaTensor() const { return inertiaTensor; }
void RigidBody::ApplyForce(const Force& force) { this -> force = force; }
void RigidBody::ApplyTorque(const Torque& torque) { this -> torque = torque; }

void RigidBody::Update(float deltaTime) {

    // Linear motion
    Vector3 forceVector = force.getValue();
    acceleration = forceVector * (1.0f / mass);
    velocity = velocity + acceleration * deltaTime;
    position = position + velocity * deltaTime;

    // Rotational motion
    Vector3 torqueVector = torque.getValue();
    angularAcceleration = inertiaTensor.inverse() * torqueVector;
    angularVelocity = angularVelocity + angularAcceleration * deltaTime;

    float angularSpeed = angularVelocity.magnitude();

    if (angularSpeed > 0.0f) {
        Vector3 rotationAxis = angularVelocity.normalized();
        float rotationAngle = angularSpeed * deltaTime;
        Quaternion deltaRotation =  Quaternion::fromAxisAngle( rotationAxis, rotationAngle );
        orientation = orientation .multiplication(deltaRotation).normalize();
    }
}