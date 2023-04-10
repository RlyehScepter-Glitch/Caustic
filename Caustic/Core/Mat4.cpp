#include "Mat4.h"

namespace Caustic
{

    Mat4::Mat4()
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                m_Data[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }

    float& Mat4::operator()(int row, int col)
    {
        return m_Data[row][col];
    }

    const float& Mat4::operator()(int row, int col) const
    {
        return m_Data[row][col];
    }

    Mat4 Mat4::operator*(const Mat4& other) const
    {
        Mat4 result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result(i, j) = 0.0f;
                for (int k = 0; k < 4; ++k)
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    Vec3 Mat4::operator*(const Vec3& v) const
    {
        return Vec3(
            m_Data[0][0] * v.GetX() + m_Data[0][1] * v.GetY() + m_Data[0][2] * v.GetZ() + m_Data[0][3],
            m_Data[1][0] * v.GetX() + m_Data[1][1] * v.GetY() + m_Data[1][2] * v.GetZ() + m_Data[1][3],
            m_Data[2][0] * v.GetX() + m_Data[2][1] * v.GetY() + m_Data[2][2] * v.GetZ() + m_Data[2][3]
        );
    }
}