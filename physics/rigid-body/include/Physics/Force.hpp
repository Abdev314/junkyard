#ifndef FORCE_H
#define FORCE_H

#include "Math/Vector3.hpp"

class Force {

    private:
        Vector3 value;

    public:
        Force(float x, float y, float z);

        Vector3 getValue() const;
        Force operator+(const Force& other) const;
};

#endif