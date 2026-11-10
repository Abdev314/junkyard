#include "Physics/Torque.hpp"

Torque::Torque(float x, float y, float z) : value(x, y, z) {}
Vector3 Torque::getValue() const { return value; }

Torque Torque::operator+(const Torque& other) const {
    Vector3 result = value + other.value;

    return Torque(
        result.getx(),
        result.gety(),
        result.getz()
    );
}