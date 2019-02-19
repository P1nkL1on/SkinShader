#include "esprocesser.h"
#include "qdebug.h"

using namespace Eigen;

QImage EsProcesser::redrawImage(const PlaneVector &vec) const
{
    if (isPlaneVectorEmpty(vec))
        return clearImage();
    return drawer.paint(vec);
}

bool EsProcesser::isImageEmpty(const QImage &image) const
{
    return image.width() == 0 || image.height() == 0;
}

bool EsProcesser::isPlaneVectorEmpty(const PlaneVector &vec) const
{
    return vec.width() == 0 || vec.height() == 0;
}

QImage EsProcesser::clearImage() const
{
    return QImage(0,0, QImage::Format_ARGB32);
}

void EsProcesser::savePath(QString &path)
{
    lastUsedPath = path.mid(0, path.lastIndexOf('/') + 1);
}

EsProcesser::~EsProcesser()
{
    if (isModelLoaded())
        delete originalModel;
    if (isStretchedModelLoaded())
        delete strethedModel;
}

bool EsProcesser::isTexuteLoaded() const
{
    return !isPlaneVectorEmpty(loadedTexture);
}

bool EsProcesser::isStretchedTextureExist() const
{
    return !isPlaneVectorEmpty(stretchedTexture);
}

bool EsProcesser::isModelLoaded() const
{
    return originalModel != nullptr;
}

bool EsProcesser::isStretchedModelLoaded() const
{
    return strethedModel != nullptr;
}

bool EsProcesser::loadTexture(const QString &path)
{
    loadedTexture = PlaneVector(path);
    bool success = isTexuteLoaded();
    if (!success)
        return false;
    loadedTextureImage = clearImage();
    stretchedTextureImage = clearImage();
    return true;
}

void EsProcesser::loadModel(EsModel *model)
{
    if (model != nullptr)
        originalModel = model;
}

void EsProcesser::loadStretchedModel(EsModel *model)
{
    if (model != nullptr)
        strethedModel = model;
}

void EsProcesser::scaleNormallyToMax(const int newMax)
{
    if (!isTexuteLoaded())
        return;
    double k = 1.0 * newMax / (std::min(loadedTexture.width(), loadedTexture.height()));
    scaleLoadedTexture(k);
}

void EsProcesser::scaleLoadedTexture(const int newWidth, const int newHeight)
{
    if (!isTexuteLoaded())
        return;
    loadedTexture = loadedTexture.changeSize(newWidth, newHeight, 2);
}

void EsProcesser::scaleLoadedTexture(const double newScale)
{
    if (!isTexuteLoaded())
        return;
    scaleLoadedTexture(int(loadedTexture.width() * newScale), int(loadedTexture.height() * newScale));
}

void EsProcesser::stretchTexture()
{
    stretchedTextureImage = clearImage();
    if (!isTexuteLoaded()){
        qDebug() << "No texture loaded!";
        return;
    }
    if (!isModelLoaded()){
        qDebug() << "No model loaded!";
        stretchedTexture = PlaneVector::testPlaneVector(loadedTexture.width(), loadedTexture.height());
        return;
    }
    if (!isStretchedModelLoaded()){
        qDebug() << "No stretched model loaded!";
        stretchedTexture = loadedTexture;
        return;
    }

    const QVector<Matrix2d> vertTs =
            EsCalculator::transformOfEdgesForEachVertex(
                originalModel->v(),
                strethedModel->v(),
                originalModel->vt(),
                originalModel->s(),
                originalModel->st());
    qDebug() << "Each vertex Stretch Axes and Transforms calculated!";
    stretchedTexture =
            EsTexturer::applyInterpolatedTransforms(
                loadedTexture,
                vertTs,
                originalModel->vt(),
                originalModel->st());
    qDebug() << "Texture changes applied!";
}

QImage EsProcesser::getLoadedTexture()
{
    if (!isTexuteLoaded())
        return clearImage();
    if (isImageEmpty(loadedTextureImage))
        loadedTextureImage = redrawImage(loadedTexture);
    return loadedTextureImage;
}

QImage EsProcesser::getStretchedTexture()
{
    if (!isStretchedTextureExist())
        return clearImage();
    if (isImageEmpty(stretchedTextureImage))
        stretchedTextureImage = redrawImage(stretchedTexture);
    return stretchedTextureImage;
}

void EsProcesser::drawSelf(QPainter *qp)
{
    QPoint startOffset = QPoint(20, 50);
    if (isTexuteLoaded()){
        const QImage oti = getLoadedTexture();
        qp->drawImage(startOffset, oti);
        startOffset += QPoint(oti.width() + 10, 0);
    }
    if (isStretchedTextureExist()){
        const QImage sti = getStretchedTexture();
        qp->drawImage(startOffset, sti);
    }
    // else draw none
}
