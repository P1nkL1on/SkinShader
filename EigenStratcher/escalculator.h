#ifndef ESCALCULATOR_H
#define ESCALCULATOR_H

#include "esdrawer.h"
#include "string"

class esCalculator
{
public:
    esCalculator() = default;

    Eigen::Matrix<double, 3,1> centrateMatrix(const EigenFuncs::Mat33D &orig, EigenFuncs::Mat33D &res) const;
    void calculateQ (const EigenFuncs::Mat33D &V_g, const EigenFuncs::Mat33D &V_uv, EigenFuncs::Mat33D &resQ) const;
    void calculateClosestR (const EigenFuncs::Mat33D &Q, EigenFuncs::Mat33D &resR) const;
    void calculateE1E2 (const EigenFuncs::Mat23D &orig, EigenFuncs::Mat22D &res) const;
    void coutMatrix(const std::string &name, const Eigen::MatrixXd &doubleMatrix) const;
    void coutEdgeLengths(const std::string &name, const Eigen::MatrixXd &mat) const;

    void test(QPainter *qp, esDrawer *dr) const;
private:
    void test0() const;
};

#endif // ESCALCULATOR_H
