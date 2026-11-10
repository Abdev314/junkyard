#include "Math/Matrix3.hpp"
#include <cmath>

Matrix3::Matrix3(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22
) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
}

void Matrix3::set(int row, int column, float value) {
    m[row][column] = value;
}

float Matrix3::get(int row, int column) const {
    return m[row][column];
}

Matrix3 Matrix3::inverse() const {

    float determinant =
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

    if (std::abs(determinant) < 0.000001f) {
        return Matrix3(
            0, 0, 0,
            0, 0, 0,
            0, 0, 0
        );
    }

    float inverseDeterminant = 1.0f / determinant;

    return Matrix3(
        (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * inverseDeterminant,
        (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * inverseDeterminant,
        (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inverseDeterminant,

        (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * inverseDeterminant,
        (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inverseDeterminant,
        (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * inverseDeterminant,

        (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * inverseDeterminant,
        (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * inverseDeterminant,
        (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * inverseDeterminant
    );
}


Vector3 Matrix3::operator*(const Vector3& vector) const {
    return Vector3(
        m[0][0] * vector.getx() +
        m[0][1] * vector.gety() +
        m[0][2] * vector.getz(),

        m[1][0] * vector.getx() +
        m[1][1] * vector.gety() +
        m[1][2] * vector.getz(),

        m[2][0] * vector.getx() +
        m[2][1] * vector.gety() +
        m[2][2] * vector.getz()
    );
}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
    Matrix3 result(
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    );

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            float value = 0.0f;

            for (int k = 0; k < 3; k++) {
                value += m[row][k] * other.m[k][column];
            }

            result.set(row, column, value);
        }
    }

    return result;
}