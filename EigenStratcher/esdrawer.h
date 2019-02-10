#ifndef ESDRAWER_H
#define ESDRAWER_H

#include "esmodel.h"
#include <QVector2D>
#include <qpainter.h>

class EsDrawer
{
public:
    EsDrawer() = default;
    void setScale(const double scaling);

    void drawModel(QPainter *painter, const EsModel &model) const;
    void drawSystemG(QPainter *painter, const double scale) const;
    void drawSystemUV(QPainter *painter) const;
    void drawLine(QPainter *painter, const Eigen::Vector2d &v1, const Eigen::Vector2d &v2, const QColor &color = Qt::red , const float width = 1) const;
    void drawLine(QPainter *painter, const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, const QColor &color = Qt::red , const float width = 1) const;
    void drawTriangleG(QPainter *painter, const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, const Eigen::Vector3d &v3,
                       const float lineWidth = 1.0, const QVector<QColor> triangleColors = {Qt::red, Qt::green, Qt::blue}) const;
    void drawTriangleGmonocolor(QPainter *painter, const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, const Eigen::Vector3d &v3,
                       const float lineWidth = 1.0, const QColor triangleColor = Qt::gray) const;
    void drawTriangleUV(QPainter *painter, const Eigen::Vector2d &v1, const Eigen::Vector2d &v2, const Eigen::Vector2d &v3,
                        const float lineWidth = 1.0, const QVector<QColor> triangleColors = {Qt::red, Qt::green, Qt::blue}) const;
    void drawTriangleUVmonocolor(QPainter *painter, const Eigen::Vector2d &v1, const Eigen::Vector2d &v2, const Eigen::Vector2d &v3,
                        const float lineWidth = 1.0, const QColor triangleColor = Qt::gray) const;

    void debugTriangle(QPainter *painter, const Eigen::Matrix3d &mat, const QColor &fillColor = Qt::gray, const float width = 1.0) const;
    void debugTriangleUV(QPainter *painter, const Eigen::Matrix3d &mat, const QColor &fillColor = Qt::gray, const float width = 1.0) const;
//    void debugTriangle(QPainter *painter, const EigenFuncs::Mat23D &mat) const;
private:
    QVector2D translateVec3(const Eigen::Vector3d &v) const;
    QVector2D translateVec2(const Eigen::Vector2d &v, const bool isUV = true) const;
    QVector2D m_centerG = QVector2D(550, 400);
    QVector2D m_centerUV = QVector2D(150, 150);
    double m_scaling = 1.0;
    int m_sizeUV = 100;
    double m_zToXProect = -.5;
    double m_zToYProect = .5;

    void drawTriDotTriangle(QPainter *painter, const QVector<QVector2D> &dots, const float lineWidth, QVector<QColor> triangleColors) const;
};

#endif // ESDRAWER_H
