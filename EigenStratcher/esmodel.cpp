#include "esmodel.h"

using namespace EigenFuncs;

esModel::esModel(
        const QVector<Vector3D> &v,
        const QVector<Vector2D> &vt,
        const QVector<int> &s,
        const QVector<int> &st):
    m_v(v),
    m_vt(vt),
    m_s(s),
    m_st(st)
{

}

esModel esModel::createTestModel(const int modelIndex)
{
    const QVector<Vector3D> v = {makeVector3D(.0, .8, 5.0), makeVector3D(.6, 1.8,4.6), makeVector3D(1.5, -.8, 5.2),
                                 makeVector3D(2.0, 1.2, 5.0), makeVector3D(1.1, 3.8, 4.0)};
    const QVector<Vector2D> vt = {makeVector2D(.0, .0), makeVector2D(.4, .0), makeVector2D(.0, .6), makeVector2D(1.0, .0), makeVector2D(.5, .6)};
    const QVector<int> s = {0,1,2,  2,1,3,   3,1,4};
    const QVector<int> st { 4, 1, 3,  2,1,4,  2,0,1 };

    return esModel(v, vt, s, st);
}

QVector<Vector3D> esModel::v() const
{
    return m_v;
}

QVector<Vector2D> esModel::vt() const
{
    return m_vt;
}

QVector<int> esModel::s() const
{
    return m_s;
}

QVector<int> esModel::st() const
{
    return m_st;
}
