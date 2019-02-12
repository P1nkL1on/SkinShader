#include "estexturer.h"
#include "qdebug.h"

using namespace Eigen;

PlaneVector EsTexturer::applyInterpolatedTransforms(
        const PlaneVector &texture,
        const QVector<Matrix2d> &eachUvVertexTransforms,
        const QVector<Vector2d> &textureCoordinates,
        const QVector<int> &polygonIndexesTrianglulated)
{
    const int w = texture.width(), h = texture.height();

    PlaneVector result = PlaneVector(w, h);

    const int skipPixels = 0;

    for (int i = 0; i < w; i += skipPixels + 1){
        for (int j = 0; j < h; j += skipPixels + 1){
            // detect which UV polygon contains (i,j);
            const double xf = double(i) / w;
            const double yf = double(j) / h;
            int polygonIndex = -1;
            double m1, m2, m3;
            for (int p = 0; p < polygonIndexesTrianglulated.length(); p += 3){
                // polygonIndexesTrianglulated == st
                const bool isInPolygon = isBarricentered(
                            xf, yf,
                            textureCoordinates[polygonIndexesTrianglulated[p]],
                            textureCoordinates[polygonIndexesTrianglulated[p + 1]],
                            textureCoordinates[polygonIndexesTrianglulated[p + 2]],
                            m1, m2, m3);
                if (isInPolygon){
                    polygonIndex = p / 3;
                    break;
                }
            }
            if (polygonIndex < 0)
                continue;
            const Matrix2d Tpixel =
                    m1 * eachUvVertexTransforms[polygonIndexesTrianglulated[polygonIndex * 3]]
                    + m2 * eachUvVertexTransforms[polygonIndexesTrianglulated[polygonIndex * 3 + 1]]
                    + m3 * eachUvVertexTransforms[polygonIndexesTrianglulated[polygonIndex * 3 + 2]];
            // pixel stretches
            double rs, rt;
            const Matrix2d S = EsCalculator::stretchCompressAxes(Tpixel, rs, rt);
            rs = std::min(rs, 1.4);
            result.setValue(getPixelValueAfterStretching(texture, i, j, rs, S.col(0)), i, j);
        }
    }
    return result;
}
// x,y,  x1,y1 ... x3,y3
bool EsTexturer::isBarricentered(
        const double X, const double Y,
        const Eigen::Vector2d &dot1,
        const Eigen::Vector2d &dot2,
        const Eigen::Vector2d &dot3,
        double &m1, double &m2, double &m3)
{
    const double x1 = dot1(0,0), x2 = dot2(0,0), x3 = dot3(0,0),
                 y1 = dot1(1,0), y2 = dot2(1,0), y3 = dot3(1,0);
    m3 = double((Y  - y1) * (x2 - x1) - (X  - x1)*(y2 - y1))
            / ((y3 - y1) * (x2 - x1) - (x3 - x1)*(y2 - y1));

    m2 = double((Y  - y1) * (x3 - x1) - (X  - x1)*(y3 - y1))
            / ((y2 - y1) * (x3 - x1) - (x2 - x1)*(y3 - y1));

    m1 = double((Y  - y3) * (x2 - x3) - (X  - x3)*(y2 - y3))
            / ((y1 - y3) * (x2 - x3) - (x1 - x3)*(y2 - y3));

    return (m1 >= 0 && m2 >= 0 && m3 >= 0);
}


double EsTexturer::getPixelValueAfterStretching(
        const PlaneVector &texture,
        const int pixelX, const int pixelY,
        const double stretchRatio,
        const Vector2d &direction)
{
    const int interpolationType = 2;
    const double r = std::min(1.4, std::max(.7, stretchRatio));

    const double sigma = (r >= 1.0)? (38.2 * r - 26.5) : (70.5 * r - 46.9);
    const double alpha = std::min(1.0, std::min(15.4 * r - 13.8, 3.09 * (r - 1.0)));

    const int rad = 31;
    const double numSigma = 2.5;

    // direction is normilised!
    const Vector2d directionNormilised = direction / direction.norm();
    Vector2d pixelPosition;
    pixelPosition(0, 0) = double(pixelX);
    pixelPosition(1, 0) = double(pixelY);

    double gauseSummWeigth = 0;
    double gausWeigths[rad];
    for (int i = 0; i <= rad; ++i){
        const double pixelSideOffset = ( i - rad / 2.0) * numSigma / (rad - 1.0);
        gausWeigths[i] = exp(-.5 * pixelSideOffset * pixelSideOffset);
        gauseSummWeigth += gausWeigths[i];
    }

    double resultValue = 0.0;

    for (int i = 0; i <= rad; ++i){
        const double pixelSigmaSideOffset = ( i - rad / 2.0) * numSigma / (rad + 1) * sigma;
        const double colorK = (((i == rad/2)? (1.0 - alpha) : (0.0)) + alpha * gausWeigths[i] / gauseSummWeigth);

        //resultValue += getInVec(originalImage, x, y, xComponent, yComponent, pixelSigmaSideOffset, interpolationType) * colorK;
        Vector2d getColorFrom = pixelPosition + directionNormilised * pixelSigmaSideOffset;
        for (int d = 0; d < 2; ++d)
            getColorFrom(d,0) = std::max(.0, std::min(getColorFrom(d,0),  -1.0 + (d == 0? texture.width() : texture.height()) ));
        // fix corner problems ^^^
        qDebug() << pixelX << pixelY << float(getColorFrom(0,0)) <<  float(getColorFrom(1,0));
        resultValue += colorK * texture.getValue(float(getColorFrom(0,0)), float(getColorFrom(1,0)), interpolationType);
    }
    return resultValue;
}
