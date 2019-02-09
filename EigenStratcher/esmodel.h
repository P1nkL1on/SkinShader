#ifndef ESMODEL_H
#define ESMODEL_H

#include <QVector>
#include "Eigen/Core"

class EsModel
{
//  ALWAYS TRIANGULATED!
public:
    EsModel(const QVector<Eigen::Vector3d> &v, // vertices
            const QVector<Eigen::Vector2d> &vt,   // texture vertices
            const QVector<int> &s,  // indexes of 3d v-s, 0,2,3,    0,2,6  6,3,1
            const QVector<int> &st); // indexes of 2d v-s  0, 2, 3,   0,2,3   1, 2, 3

//    static EsModel createTestModel (const int modelIndex = 0);


    QVector<Eigen::Vector3d> v() const;
    QVector<Eigen::Vector2d> vt() const;
    QVector<int> s() const;
    QVector<int> st() const;

private:
    QVector<Eigen::Vector3d> m_v;
    QVector<Eigen::Vector2d> m_vt;

    QVector<int> m_s;
    QVector<int> m_st;
};

#endif // ESMODEL_H
