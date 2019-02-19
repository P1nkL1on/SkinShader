#include "escalculatorhelp.h"

#include "Shading/planevectordrawer.h"
#include "Shading/trianglespeller.h"
#include "Shading/crossshading.h"

#include "estexturer.h"

using namespace EsCalculator;
using namespace Eigen;
using namespace std;

void EsCalculatorHelp::testRandomTriangleWithPainting(QPainter *qp, EsDrawer *dr)
{
    dr->drawSystemG(qp, 5);

    const Matrix3d V_g0 = MatrixXd::Random(3,3);
    Matrix3d V_uv0 = //MatrixXd::Random(3,3);
            (Matrix3d::Identity() - MatrixXd::Random(3,3)) * .5;
    V_uv0(2,0) = V_uv0(2,1) = V_uv0(2,2) = 0.0;

    const Matrix3d V_g = centredTriangleStack(V_g0);
    const Matrix3d V_uv = centredTriangleStack(V_uv0);

    const Matrix3d Q = transformBetweenTriangles(V_g, V_uv);
    const Matrix3d R = closestRotationMatrix(Q);
    const Matrix3d V_gR = R * V_g;

    const Matrix2d e12 = edgeStack(V_uv);
    const Matrix2d e12_R = edgeStack(V_gR);

    const Matrix2d T = transformBetweenEdgePair(e12, e12_R);

    //        traceMatrix(e12, "e12");
    //        traceMatrix(e12_R, "e12 '");
    //        traceMatrix(T, "T");
    //        const Matrix2d tt = T * e12;
    //        traceMatrix((tt), "T * e12");

    const Matrix2d S = stretchCompressAxesOld(Q, R, T);
    traceMatrix(S);

    //    dr->debugTriangle(qp, V_g);
    dr->debugTriangle(qp, V_uv0, QColor(200, 20, 250, 20));
    dr->debugTriangle(qp, V_uv, QColor(40, 40, 200, 100));
    dr->debugTriangle(qp, V_gR, QColor(0, 200, 0, 150));

    //    coutEdgeLengths("v_g", V_g);
    //    coutEdgeLengths("v_gR", V_gR);
    //    coutEdgeLengths("v_uv", V_uv);

    //    coutMatrix("v_gR", V_gR);
    //    coutMatrix("v_uv", V_uv);
    const double uNorm = S.col(0).norm(),
            vNorm = S.col(1).norm();

    // haha!
    //cout << endl << uNorm * svd.singularValues()(0,0) << "  " << vNorm * svd.singularValues()(1,0)<< endl;

    const Vector2d zer = Vector2d::Zero();
    const Vector2d stretchAxis = S.col(0) * .2;
    const Vector2d compressAxis = S.col(1) * .2;

    dr->drawLine(qp, zer, stretchAxis, QColor(30, 30, 200), 2);
    dr->drawLine(qp, zer, compressAxis, Qt::red, 2);
}

void EsCalculatorHelp::testRandom2TriangleWithPainting(QPainter *qp, EsDrawer *dr)
{
    dr->drawSystemG(qp, 3);
    //    dr->drawSystemUV(qp);

    const Matrix3d triangleStack = MatrixXd::Random(3,3) + 2 * Matrix3d::Ones();
    const Matrix3d targetTriangleStack = triangleStack + .5 * MatrixXd::Random(3,3) + Matrix3d::Ones();
    Matrix3d triangleUvTriangleStack = MatrixXd::Random(3,3);
    triangleUvTriangleStack = (triangleUvTriangleStack + Matrix3d::Ones()) * .5;
    triangleUvTriangleStack(2,0) = triangleUvTriangleStack(2,1) = triangleUvTriangleStack(2,2) = 0.0;

    dr->debugTriangle(qp, triangleStack, Qt::darkRed);
    dr->debugTriangle(qp, targetTriangleStack, Qt::darkBlue);
    dr->debugTriangleUV(qp, triangleUvTriangleStack, Qt::darkYellow);

    const Matrix3d Vg0 = centredTriangleStack(triangleStack);
    const Matrix3d VgT = centredTriangleStack(targetTriangleStack);
    Matrix3d Vuv;
    const Vector2d uvCenter = centredTriangleStack(triangleUvTriangleStack, Vuv).head(2);

    dr->debugTriangle(qp, Vg0, Qt::red);
    dr->debugTriangle(qp, VgT, Qt::blue);
    dr->debugTriangleUV(qp, Vuv, Qt::yellow);

    // V_g0 -> V_g1
    // Q0 * V_g0 = V_uv, Q1 * V_g1 = V_uv
    // Q0 =V_uv * V_g0-1, etc
    const Matrix3d Q0 = transformBetweenTriangles(Vg0, Vuv);
    const Matrix3d QT = transformBetweenTriangles(VgT, Vuv);

    // R0 = R0(Q0)
    const Matrix3d R0 = closestRotationMatrix(Q0);
    const Matrix3d RT = closestRotationMatrix(QT);

    const Matrix2d e12 = edgeStack(R0 * Vg0);
    const Matrix2d e12_R = edgeStack(RT * VgT);

    dr->debugTriangleUV(qp, R0 * Vg0, Qt::red);
    dr->debugTriangleUV(qp, RT * VgT, Qt::blue);
    // T = ...
    const Matrix2d T = transformBetweenEdgePair(e12, e12_R);

    //
    //const Matrix3d QS = transformBetweenTriangles(Vg0, VgT);
    //const Matrix3d RS = closestRotationMatrix(QS);
    double rs, rt;
    const Matrix2d S = stretchCompressAxes(T, rs, rt);

    //
    // const Vector2d zer = Vector2d::Zero();
    dr->drawLine(qp, uvCenter, uvCenter + S.col(0) * .4, QColor(0,250,250), 2);
    dr->drawLine(qp, uvCenter, uvCenter + S.col(1) * .4, QColor(250,250,0), 2);
    return;
}

int tfx(const int X){
    return (X - 1950) / 2 + 450;
}
int tfy(const int Y){
     return (Y - 1000) / 2 + 450;
}

int offset = 0;

void EsCalculatorHelp::testRandom3Model(QPainter *qp, EsDrawer *dr)
{
//    const int size = 100;
//    const int pixelPerPixel = 400 / size;
//    PlaneVector D = PlaneVector("test.png");
//    PlaneVector DS = PlaneVector(size, size);
//    PlaneVector Dfin = PlaneVector(600, 600);
//    D = D.changeSize(size, size, 1);

    PlaneVectorDrawer p = PlaneVectorDrawer();
//    p.mash = pixelPerPixel;
//    p.paint(qp,D, 20, 50);

//    const QVector<Vector3d> v = {makeVector3D(.0, .8, 5.0), makeVector3D(.6, 1.8,4.6), makeVector3D(1.5, -.8, 5.2),
//                                 makeVector3D(2.0, 1.2, 5.0), makeVector3D(1.1, 3.8, 4.0)};
    const QVector<Vector3d> v = {makeVector3D(.2, .2, .15), makeVector3D(.2, -4.0, .15), makeVector3D(2.6, .2, .15),
                                 makeVector3D(2.6, -4.0, .15), makeVector3D(4.0, .2, .15)};
    const QVector<Vector2d> vt = {makeVector2D(.0, .0), makeVector2D(.0, 1.0), makeVector2D(.6, .0),makeVector2D(.6, 1.0), makeVector2D(1.0, .0)};
    QVector<Vector3d> v2 = v;
    for (int i = 0; i < v.length(); ++i){
        v2[i] += makeVector3D(5.0, .0, .0) + MatrixXd::Random(3, 1) * .5;
//        if (i == 0)
//            v2[i] += .02 * (makeVector3D(-(++offset), +(offset), 0));
    }
//    const QVector<Vector2d> vt = {makeVector2D(.0, .0), makeVector2D(.4, .0), makeVector2D(.0, .6), makeVector2D(1.0, .0), makeVector2D(.5, .6)};
//    const QVector<int> s = {0,1,2,  2,1,3,   3,1,4};
//    const QVector<int> st { 4, 1, 3,  2,1,4,  2,0,1 };
    const QVector<int> s = {0,2, 1,  2, 3, 1,  4, 3, 2};
    const QVector<int> st = {0,2, 1,  2, 3, 1,  4, 3, 2};

    EsModel model = EsModel(v, vt, s, st);
    EsModel model2 = EsModel(v2, vt, s, st);
    vector<int> modelDots, model2Dots;

    dr->drawModel(qp, model, modelDots, Qt::red);
    dr->drawModel(qp, model2, model2Dots, Qt::blue);

    const int polyCount = s.length() / 3;
    for (int polIndex = 0; polIndex < polyCount; polIndex++){
        const Matrix3d poly = makeMatrixFromVectors3D(v[s[polIndex * 3]], v[s[polIndex * 3 + 1]], v[s[polIndex * 3 + 2]]);
        const Matrix3d polyTarg = makeMatrixFromVectors3D(v2[s[polIndex * 3]], v2[s[polIndex * 3 + 1]], v2[s[polIndex * 3 + 2]]);
        const Matrix3d polyUV = makeMatrixFromVectors2D(vt[st[polIndex * 3]], vt[st[polIndex * 3 + 1]], vt[st[polIndex * 3 + 2]]);

        double rs,rt;
        const Matrix2d S = stretchCompressAxes(poly, polyTarg, polyUV, rs, rt);
        Matrix3d centredUV;
        const Vector2d uvCenter = centredTriangleStack(polyUV, centredUV).head(2);
        dr->drawLine(qp, uvCenter, uvCenter + S.col(0) * .1 * rs, QColor(0,250,250), 2);
        dr->drawLine(qp, uvCenter, uvCenter + S.col(1) * .1 * rt, QColor(250,250,0), 2);

//        CrossShading cs = CrossShading();
//        const int i = polIndex;
//        cs.blurPixelsInTriangleCross(
//             D, DS,
//             float(vt[st[i]](0,0)), float(vt[st[i]](1,0)),
//             float(vt[st[i + 1]](0,0)), float(vt[st[i + 1]](1,0)),
//             float(vt[st[i + 2]](0,0)), float(vt[st[i + 2]](1,0)),
//             rs, rt, S(0,0), S(1,0), 2);
    }

    const QVector<Matrix2d> vertTs =
            transformOfEdgesForEachVertex(v, v2, vt, s, st);
    const int textureSize = 120;
    PlaneVector D = PlaneVector("test.png");
    if (D.width() == 0){
        cout << "Error in loading!" << endl;
        return;
    }
    D = D.changeSize(textureSize, textureSize, 2);
    PlaneVector Dsmooth = EsTexturer::applyInterpolatedTransforms(D, vertTs, vt, st);
    p.paint(qp, D, 425, 25);
    p.paint(qp, Dsmooth, 445 + textureSize * p.mash, 25);


    return;





    // drawing only
    for (int vIndex = 0; vIndex < v.length(); ++vIndex){
        double rs, rt;
        const Matrix2d S = stretchCompressAxes(vertTs[vIndex], rs, rt);
        const Vector2d uvCenter = vt[vIndex];
        dr->drawLine(qp, uvCenter, uvCenter + S.col(0) * .1 * rs, QColor(89, 100, 155), 2);
//        dr->drawLine(qp, uvCenter, uvCenter + S.col(1) * .1 * rt, QColor(252, 113, 162), 2);
    }
    const int textureWidth = 40;
    const int textureHeight = 40;

    for (int i = 0; i <= textureWidth; ++i){
        for (int j = 0; j <= textureHeight; ++j){
            for (int p = 0; p < st.length(); p += 3){
                float a, b, c;
                TriangleSpeller::ballicentrate(float(i) / textureWidth, float(j) / textureHeight,
                        float(vt[st[p]](0,0)),float(vt[st[p]](1,0)),
                        float(vt[st[p + 1]](0,0)),float(vt[st[p + 1]](1,0)),
                        float(vt[st[p + 2]](0,0)),float(vt[st[p + 2]](1,0)),
                        a,b,c);
                if (!(a >= 0 && b >= 0 && c >= 0))
                    continue;
                const Matrix2d Tsv =
                        vertTs[st[p]] * a
                        + vertTs[st[p + 1]] * b
                        + vertTs[st[p + 2]] * c;

                double rs, rt;
                const Matrix2d S = stretchCompressAxes(Tsv, rs, rt);

                const Vector2d uvCenter = makeVector2D(float(i) / textureWidth, float(j) / textureHeight);
                //const Vector2d uF = uvCenter + S.col(0) * (-.025 * rs);
                const Vector2d uT = uvCenter + S.col(0) * .25 * ( rs - 1.0);

                dr->drawLine(qp, uvCenter, uT, QColor(129, 170, 255), 2);
                dr->drawLine(qp, uvCenter, uvCenter, Qt::red, 2);

                //dr->drawLine(qp, uvCenter, uvCenter + S.col(1) * .05 * rt, QColor(252, 213, 222), 2);
            }
        }
    }

//    for (int i = 0; i < modelDots.size(); i += 6){ // poly index
//        TriangleSpeller::fillTexture(D, Dfin,
//                float(vt[st[i / 2]](0,0)), float(vt[st[i / 2]](1,0)),
//                float(vt[st[i / 2 + 1]](0,0)), float(vt[st[i / 2 + 1]](1,0)),
//                float(vt[st[i / 2 + 2]](0,0)), float(vt[st[i / 2 + 2]](1,0)),
//                tfx(modelDots[i]), tfy(modelDots[i + 1]),
//                tfx(modelDots[i + 2]), tfy(modelDots[i + 3]),
//                tfx(modelDots[i + 4]), tfy(modelDots[i + 5]));
//        TriangleSpeller::fillTexture(DS, Dfin,
//                float(vt[st[i / 2]](0,0)), float(vt[st[i / 2]](1,0)),
//                float(vt[st[i / 2 + 1]](0,0)), float(vt[st[i / 2 + 1]](1,0)),
//                float(vt[st[i / 2 + 2]](0,0)), float(vt[st[i / 2 + 2]](1,0)),
//                tfx(model2Dots[i]), tfy(model2Dots[i + 1]),
//                tfx(model2Dots[i + 2]), tfy(model2Dots[i + 3]),
//                tfx(model2Dots[i + 4]), tfy(model2Dots[i + 5]));
//    }
//    p.paint(qp, DS, 550, 50);
//    p.mash = 1;
//    p.paint(qp,Dfin, 150, 470);
}

Vector2d EsCalculatorHelp::makeVector2D(const double x, const double y)
{
    Vector2d res;
    res << x, y;
    return res;
}

Vector3d EsCalculatorHelp::makeVector3D(const double x, const double y, const double z)
{
    Vector3d res;
    res << x, y, z;
    return res;
}

Matrix3d EsCalculatorHelp::makeMatrixFromVectors3D(const Vector3d &dot0, const Vector3d &dot1, const Vector3d &dot2)
{
    Matrix3d mat;
    mat.col(0) = dot0;
    mat.col(1) = dot1;
    mat.col(2) = dot2;
    return mat;
}

Matrix3d EsCalculatorHelp::makeMatrixFromVectors2D(const Vector2d &dot0, const Vector2d &dot1, const Vector2d &dot2)
{
    Matrix3d mat;
    mat << dot0(0,0), dot1(0,0), dot2(0,0),  dot0(1,0), dot1(1,0), dot2(1,0), 0,0,0;
    return mat;
}

EsModel *EsCalculatorHelp::testModel1()
{
    const QVector<Vector3d> v = {makeVector3D(.2, .2, .15), makeVector3D(.2, -4.0, .15), makeVector3D(2.6, .2, .15),
                                 makeVector3D(2.6, -4.0, .15), makeVector3D(4.0, .2, .15)};
    const QVector<Vector2d> vt = {makeVector2D(.0, .0), makeVector2D(.0, 1.0), makeVector2D(.6, .0),makeVector2D(.6, 1.0), makeVector2D(1.0, .0)};

    const QVector<int> s = {0,2, 1,  2, 3, 1,  4, 3, 2};
    const QVector<int> st = {0,2, 1,  2, 3, 1,  4, 3, 2};

    return new EsModel(v, vt, s, st);
}

EsModel *EsCalculatorHelp::testModelRandomBend(const EsModel &model)
{
    QVector<Vector3d> vOrig = model.v();
    for (int i = 0; i < vOrig.length(); ++i){
        vOrig[i] += makeVector3D(5.0, .0, .0) + MatrixXd::Random(3, 1) * .5;
    }

    return new EsModel(vOrig, model.vt(), model.s(), model.st());
}
