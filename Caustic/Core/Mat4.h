#pragma once

#include "Vec3.h"

namespace Caustic 
{
    class Mat4 
    {
    public:
        // Constructor
        Mat4();

        // Accessor functions for accessing elements of the matrix
        float& operator()(int row, int col);
        const float& operator()(int row, int col) const;

        // Matrix multiplication operator
        Mat4 operator*(const Mat4& other) const;

        // Matrix-vector multiplication operator
        Vec3 operator*(const Vec3& v) const;
    private:
        float m_Data[4][4];
    };
}