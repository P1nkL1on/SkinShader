#ifndef ESDRAWER_H
#define ESDRAWER_H

#include "esmodel.h"
#include <QVector2D>
#include <qpainter.h>

class esDrawer
{
public:
    esDrawer() = default;
    void setScale(const double scaling);

    void drawModel(QPainter *painter, const esModel &model) const;
    void drawSystemG(QPainter *painter, const double scale) const;
    void drawLine(QPainter *painter, const EigenFuncs::Vector3D &v1, const EigenFuncs::Vector3D &v2, const QColor &color = Qt::red ) const;
    void drawTriangleG(QPainter *painter, const EigenFuncs::Vector3D &v1, const EigenFuncs::Vector3D &v2, const EigenFuncs::Vector3D &v3,
                       const float lineWidth = 1.0, const QVector<QColor> triangleColors = {Qt::red, Qt::green, Qt::blue}) const;
    void drawTriangleGmonocolor(QPainter *painter, const EigenFuncs::Vector3D &v1, const EigenFuncs::Vector3D &v2, const EigenFuncs::Vector3D &v3,
                       const float lineWidth = 1.0, const QColor triangleColor = Qt::gray) const;
    void drawTriangleUV(QPainter *painter, const EigenFuncs::Vector2D &v1, const EigenFuncs::Vector2D &v2, const EigenFuncs::Vector2D &v3,
                        const float lineWidth = 1.0, const QVector<QColor> triangleColors = {Qt::red, Qt::green, Qt::blue}) const;
    void drawTriangleUVmonocolor(QPainter *painter, const EigenFuncs::Vector2D &v1, const EigenFuncs::Vector2D &v2, const EigenFuncs::Vector2D &v3,
                        const float lineWidth = 1.0, const QColor triangleColor = Qt::gray) const;

    void debugTriangle(QPainter *painter, const EigenFuncs::Mat33D &mat) const;
    void debugTriangle(QPainter *painter, const EigenFuncs::Mat23D &mat) const;
private:
    QVector2D translateVec3(const EigenFuncs::Vector3D &v) const;
    QVector2D translateVec2(const EigenFuncs::Vector2D &v) const;
    QVector2D m_centerG = QVector2D(550, 400);
    QVector2D m_centerUV = QVector2D(20, 20);
    double m_scaling = 1.0;
    int m_sizeUV = 150;
    double m_zToXProect = -.5;
    double m_zToYProect = .5;

    void drawTriDotTriangle(QPainter *painter, const QVector<QVector2D> &dots, const float lineWidth, QVector<QColor> triangleColors) const;
};

#endif // ESDRAWER_H
