#include "esdrawer.h"

using namespace EigenFuncs;

void esDrawer::setScale(const double scaling)
{
    m_scaling = scaling;
}

QColor mixColor(double k){
    const int val = int(k * 255);
    return QColor(val,val,val);
}

void esDrawer::drawModel(QPainter *painter, const esModel &model) const
{
    const auto v = model.v();
    const auto vt = model.vt();
    const auto s = model.s();
    const auto st = model.st();

    if (st.length() % 3 != 0)
        return;
    for (int i = 0; i < st.length(); i+=3)
        drawTriangleUVmonocolor(painter, vt[st[i]], vt[st[i + 1]], vt[st[i + 2]], 4 - i / 3,mixColor(1.0 * i / st.length()));

    drawSystemG(painter, 5.0);

    const int polygonCount = s.length() / 3;
    for (int i = 0; i < s.length(); i+=3)
        drawTriangleGmonocolor(painter, v[s[i]], v[s[i + 1]], v[s[i + 2]], 2, mixColor(1.0 * (i/3) / polygonCount));
}

void esDrawer::drawSystemG(QPainter *painter, const double scale) const
{
    Vector3D zero = makeVector3D(0,0,0);
    Vector3D zeroX = makeVector3D(scale,0,0);
    Vector3D zeroY = makeVector3D(0,scale,0);
    Vector3D zeroZ = makeVector3D(0,0,scale);
    drawLine(painter, zero, zeroX, Qt::red);
    drawLine(painter, zero, zeroY, Qt::green);
    drawLine(painter, zero, zeroZ, Qt::blue);
}

void esDrawer::drawLine(QPainter *painter, const Vector3D &v1, const Vector3D &v2, const QColor &color) const
{
    const auto from = translateVec3(v1);
    const auto to = translateVec3(v2);
    painter->setPen(QPen(color));
    painter->drawLine(from.x(), from.y(), to.x(), to.y());
}

//drawTriangleG(painter, v1,v2,v3);
void esDrawer::drawTriangleG(QPainter *painter,
                             const Vector3D &v1, const Vector3D &v2, const Vector3D &v3,
                             const float lineWidth, const QVector<QColor> triangleColors) const
{
    if (triangleColors.length() != 3)
        return;
    QVector<QVector2D> planeC = { translateVec3(v1), translateVec3(v2), translateVec3(v3) };
    for (int i = 0; i < 3; ++i){
        Vector3D proect = (i == 0)? v1 : ((i == 1)? v2 : v3);

        Vector3D from = proect;
        from(0, 1) = 0.0;
        Vector3D from2 = from;
        from2(0,0) = 0.0;
        Vector3D from3 = from;
        from3(0,2) = 0.0;
        drawLine(painter, proect, from, Qt::green);
        drawLine(painter, from2, from, Qt::red);
        drawLine(painter, from3, from, Qt::blue);

    }
    drawTriDotTriangle(painter, planeC, lineWidth, triangleColors);
}

void esDrawer::drawTriangleGmonocolor(QPainter *painter, const Vector3D &v1, const Vector3D &v2, const Vector3D &v3, const float lineWidth, const QColor triangleColor) const
{
    drawTriangleG(painter, v1,v2,v3, lineWidth, {triangleColor, triangleColor, triangleColor});
}

void esDrawer::drawTriangleUV(QPainter *painter, const Vector2D &v1, const Vector2D &v2, const Vector2D &v3, const float lineWidth, const QVector<QColor> triangleColors) const
{
    if (triangleColors.length() != 3)
        return;
    QVector<QVector2D> planeC = { translateVec2(v1), translateVec2(v2), translateVec2(v3) };
    drawTriDotTriangle(painter, planeC, lineWidth, triangleColors);
}

void esDrawer::drawTriangleUVmonocolor(QPainter *painter, const Vector2D &v1, const Vector2D &v2, const Vector2D &v3, const float lineWidth, const QColor triangleColor) const
{
    drawTriangleUV(painter, v1,v2,v3, lineWidth, {triangleColor, triangleColor, triangleColor});
}

void esDrawer::debugTriangle(QPainter *painter, const Mat33D &mat) const
{
    drawTriangleG(painter,
                  makeVector3D(mat(0,0), mat(1,0), mat(2,0)),
                  makeVector3D(mat(0,1), mat(1,1), mat(2,1)),
                  makeVector3D(mat(0,2), mat(1,2), mat(2,2)));
}

void esDrawer::debugTriangle(QPainter *painter, const Mat23D &mat) const
{
    drawTriangleG(painter,
               makeVector3D(mat(0,0), mat(1,0), .0),
               makeVector3D(mat(0,1), mat(1,1), .0),
               makeVector3D(mat(0,2), mat(1,2), .0));
}

QVector2D esDrawer::translateVec3(const Vector3D &v) const
{
    return QVector2D((int)(m_scaling * (v(0,0) + m_zToXProect * v(0,2))) + m_centerG.x(),
                     (int)(m_scaling * (- v(0,1) + m_zToYProect * v(0,2))) + m_centerG.y());
}

QVector2D esDrawer::translateVec2(const Vector2D &v) const
{
    return QVector2D((int)(m_sizeUV * v(0,0)) + m_centerUV.x(),
                     (int)(m_sizeUV * v(0,1)) + m_centerUV.y());
}

int colorSwap = 0;
void esDrawer::drawTriDotTriangle(QPainter *painter, const QVector<QVector2D> &dots, const float lineWidth, QVector<QColor> triangleColors) const
{
    if (triangleColors.length() != 3 || dots.length() != 3)
        return;
    QPolygon p;
    p << QPoint(dots[0].x(), dots[0].y())
        << QPoint(dots[1].x(), dots[1].y())
        << QPoint(dots[2].x(), dots[2].y());
    const int cl = colorSwap % 3;
    ++colorSwap;
    painter->setBrush(QColor(triangleColors[cl].red(),triangleColors[cl].green(), triangleColors[cl].blue(), 50));
    painter->drawPolygon(p);
    return;
    for (int from = 0; from < 3; ++from){
        const int to = (from + 1) % 3;
        painter->setPen(QPen(triangleColors[from], lineWidth));
        painter->drawLine(dots[from].x(), dots[from].y(), dots[to].x(), dots[to].y());
    }
}
