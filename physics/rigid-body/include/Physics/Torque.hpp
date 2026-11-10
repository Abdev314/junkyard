#ifndef TORQUE_H
#define TORQUE_H

#include "Math/Vector3.hpp"

class Torque {

private:
    Vector3 value;

public:
    Torque(float x, float y, float z);

    Vector3 getValue() const;
    Torque operator+(const Torque& other) const;

};

#endif