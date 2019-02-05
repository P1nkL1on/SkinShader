#ifndef ESMODEL_H
#define ESMODEL_H

#include <QVector>
#include "esfuncs.h"


class esModel
{
//  ALWAYS TRIANGULATED!
public:
    esModel(const QVector<EigenFuncs::Vector3D> &v, // vertices
            const QVector<EigenFuncs::Vector2D> &vt,   // texture vertices
            const QVector<int> &s,  // indexes of 3d v-s, 0,2,3,    0,2,6  6,3,1
            const QVector<int> &st); // indexes of 2d v-s  0, 2, 3,   0,2,3   1, 2, 3

    static esModel createTestModel (const int modelIndex = 0);


    QVector<EigenFuncs::Vector3D> v() const;
    QVector<EigenFuncs::Vector2D> vt() const;
    QVector<int> s() const;
    QVector<int> st() const;

private:
    QVector<EigenFuncs::Vector3D> m_v;
    QVector<EigenFuncs::Vector2D> m_vt;

    QVector<int> m_s;
    QVector<int> m_st;
};

#endif // ESMODEL_H
