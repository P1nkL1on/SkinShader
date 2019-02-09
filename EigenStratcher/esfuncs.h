#ifndef ESFUNCS_H
#define ESFUNCS_H

#include <iostream>
#include "Eigen/core"

namespace EigenFuncs{

template <typename Scalar>
using Vector2 = Eigen::Matrix<Scalar,1,2>;

template <typename Scalar>
using Vector3 = Eigen::Matrix<Scalar,1,3>;

template <typename Scalar>
using Mat33 = Eigen::Matrix<Scalar,3,3>;

using Vector2D = Vector2<double>;
using Vector3D = Vector3<double>;
using Mat33D = Mat33<double>;
using Mat23D = Eigen::Matrix<double,2,3>;
using Mat22D = Eigen::Matrix<double,2,2>;

template <typename Scalar>
inline void traceVector3 (const Vector3<Scalar> &v)
{
    std::cout << "v3" << std::endl;
    std::cout << v << std::endl;
}
template <typename Scalar>
inline void traceVector2 (const Vector2<Scalar> &v)
{
    std::cout << "v2" << std::endl;
    std::cout << v << std::endl;
}

inline Vector3D makeVector3D (const double a, const double b, const double c)
{
    Vector3D res;
    res << a,b,c;
    return res;
}
inline Vector2D makeVector2D (const double u, const double v)
{
    Vector2D res;
    res << u, v;
    return res;
}
inline Mat33D makeMat33DFrom3Vector3D(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3)
{
    Mat33D res;
    res << v1(0,0), v2(0,0), v3(0,0), v1(0,1), v2(0,1), v3(0,1), v1(0,2), v2(0,2), v3(0,2);
    return res;
}
inline Mat23D makeMat23DFrom3Vector2D(const Vector2D &v1, const Vector2D &v2, const Vector2D &v3)
{
    Mat23D res;
    res << v1(0,0), v2(0,0), v3(0,0), v1(0,1), v2(0,1), v3(0,1);
    return res;
}

}

#endif // ESFUNCS_H
