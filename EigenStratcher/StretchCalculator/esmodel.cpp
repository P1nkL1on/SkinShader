#include "esmodel.h"

using namespace Eigen;

EsModel::EsModel(
        const QVector<Vector3d> &v,
        const QVector<Vector2d> &vt,
        const QVector<int> &s,
        const QVector<int> &st):
    m_v(v),
    m_vt(vt),
    m_s(s),
    m_st(st)
{

}

//EsModel EsModel::createTestModel(const int modelIndex)
//{
//    const QVector<Vector3d> v = {makeVector3D(.0, .8, 5.0), makeVector3D(.6, 1.8,4.6), makeVector3D(1.5, -.8, 5.2),
//                                 makeVector3D(2.0, 1.2, 5.0), makeVector3D(1.1, 3.8, 4.0)};
//    const QVector<Vector2d> vt = {makeVector2D(.0, .0), makeVector2D(.4, .0), makeVector2D(.0, .6), makeVector2D(1.0, .0), makeVector2D(.5, .6)};
//    const QVector<int> s = {0,1,2,  2,1,3,   3,1,4};
//    const QVector<int> st { 4, 1, 3,  2,1,4,  2,0,1 };

//    return EsModel(v, vt, s, st);
//}

QVector<Vector3d> EsModel::v() const
{
    return m_v;
}

QVector<Vector2d> EsModel::vt() const
{
    return m_vt;
}

QVector<int> EsModel::s() const
{
    return m_s;
}

QVector<int> EsModel::st() const
{
    return m_st;
}

void EsModel::setV(const QVector<Vector3d> &newV)
{
    m_v = newV;
}
