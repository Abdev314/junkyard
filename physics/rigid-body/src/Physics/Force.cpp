#include "Physics/Force.hpp"

Force::Force(float x, float y, float z) : value(x, y, z){}
Vector3 Force::getValue() const { return value; }

Force Force::operator+(const Force& other) const {
    Vector3 result = value + other.value;

    return Force(
        result.getx(),
        result.gety(),
        result.getz()
    );
}