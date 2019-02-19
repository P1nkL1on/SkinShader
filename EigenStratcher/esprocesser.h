#ifndef ESPROCESSER_H
#define ESPROCESSER_H

#include "estexturer.h"
#include "Shading/planevectordrawer.h"

class EsProcesser
{
private:
    PlaneVectorDrawer drawer;

    QString lastUsedPath;

    PlaneVector loadedTexture;
    PlaneVector stretchedTexture;

    QImage loadedTextureImage;
    QImage stretchedTextureImage;

    QImage redrawImage(const PlaneVector &vec) const;
    bool isImageEmpty(const QImage &image) const;
    bool isPlaneVectorEmpty(const PlaneVector &vec) const;
    QImage clearImage() const;
    void savePath(QString &path);
public:
    EsProcesser() = default;
    bool isTexuteLoaded() const;
    bool isStretchedTextureExist() const;
    bool isModelLoaded() const;
    bool isStretchedModelLoaded() const;

    bool loadTexture(const QString &path);
    bool loadModel(const QString &path);
    bool loadStretchedModel(const QString &path);

    void scaleNormallyToMax(const int newMax);
    void scaleLoadedTexture(const double newScale);
    void scaleLoadedTexture(const int newWidth, const int newHeight);
    void stretchTexture();

    QImage getLoadedTexture();
    QImage getStretchedTexture();

    void drawSelf(QPainter *qp);
};

#endif // ESPROCESSER_H
