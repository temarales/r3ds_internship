#include "model.h"

Model::Model()
{

}

Model::Model(QVector<QVector3D> inVertices, QVector<QVector2D> inTextureVertices,
             QVector<int> inFaceVertexIndices, QVector<int> inFaceTextureVertexIndices, QVector<int> inFaceNormalIndices,
             QVector<int> inStartPointers)
{
    vertices = inVertices;
    textureVertices = inTextureVertices;
    faceVertexIndices = inFaceVertexIndices;
    faceVertexTextureIndices = inFaceTextureVertexIndices;
    faceNormalIndices = inFaceNormalIndices;
    startPolygonOffsets = inStartPointers;
}

Model Model::modelFromFile(const QString &filename)
{
    QString error = nullptr;
    QVector<QVector3D> newVertices;
    QVector<QVector2D> newTextureVertices;
    QVector<int> newFaceVertexIndices;
    QVector<int> newFaceVertexTextureIndices;
    QVector<int> newFaceNormalIndices;
    QVector<int> newStartPointers;

    ObjParser::fileImport(filename, newVertices, newTextureVertices, newFaceVertexIndices,
                           newFaceVertexTextureIndices, newFaceNormalIndices, newStartPointers, error);

    Model newModel(newVertices, newTextureVertices, newFaceVertexIndices,
                    newFaceVertexTextureIndices, newFaceNormalIndices, newStartPointers);
    return newModel;
}

QVector3D Model::getVertexByTriangledFaceVertexIndex(int indexInTriangledFaceVertexIndices)
{
    return this->vertices[this->triangledFaceVertexIndices[indexInTriangledFaceVertexIndices] - 1];
}

void Model::drawTriangledGrid(QOpenGLWidget* widget)
{
    widget->makeCurrent();
    glColor3d(1,0,0);
    glLineWidth(4);
    for (int i = 0; i < this->triangledFaceVertexIndices.count(); i += 3) {
        glBegin(GL_LINES);
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i] - 1].z());
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i+1] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i+1] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i+1] - 1].z());
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i+1] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i+1] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i+1] - 1].z());
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i+2] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i+2] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i+2] - 1].z());
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i] - 1].z());
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i+2] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i+2] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i+2] - 1].z());
        glEnd();
    }
    widget->doneCurrent();
}

void Model::drawOriginalGrid(QOpenGLWidget* widget)
{

}

void Model::draw(QOpenGLWidget* widget)
{
    widget->makeCurrent();
    glColor3d(1,1,0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    for (int i = 0; i < this->triangledFaceVertexIndices.count(); i += 3) {
        glBegin(GL_POLYGON);
        //glPushMatrix();
        glNormal3f(this->normalsForVertices[this->triangledFaceVertexIndices[i] - 1].x(),
                this->normalsForVertices[this->triangledFaceVertexIndices[i] - 1].y(),
                this->normalsForVertices[this->triangledFaceVertexIndices[i] - 1].z());
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i] - 1].z());
        glNormal3f(this->normalsForVertices[this->triangledFaceVertexIndices[i + 1] - 1].x(),
                this->normalsForVertices[this->triangledFaceVertexIndices[i + 1] - 1].y(),
                this->normalsForVertices[this->triangledFaceVertexIndices[i + 1] - 1].z());
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i + 1] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i + 1] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i + 1] - 1].z());
        glNormal3f(this->normalsForVertices[this->triangledFaceVertexIndices[i + 2] - 1].x(),
                this->normalsForVertices[this->triangledFaceVertexIndices[i + 2] - 1].y(),
                this->normalsForVertices[this->triangledFaceVertexIndices[i + 2] - 1].z());
        glVertex3f(
                    this->vertices[this->triangledFaceVertexIndices[i + 2] - 1].x(),
                this->vertices[this->triangledFaceVertexIndices[i + 2] - 1].y(),
                this->vertices[this->triangledFaceVertexIndices[i + 2] - 1].z());
        glEnd();
        //glPopMatrix();
    }
    glFlush();
    widget->doneCurrent();
}


void Model::triangulate(QString &error)
{
    QVector<int> triangledFaceTextureVertexIndices;
    QVector<int> triangledFaceVertexIndices;
    Q_ASSERT(!this->faceVertexTextureIndices.count() == 0);
    /*if (this->faceVertexTextureIndices.count() == 0) {
        error = "Triangulation has crashed, there are no texture vertices\n";
    }*/
    TranformationsForModel::triangulate(
                triangledFaceTextureVertexIndices, triangledFaceVertexIndices,
                this->startPolygonOffsets, this->faceVertexIndices, this->faceVertexTextureIndices);
    this->triangledFaceTextureVertexIndices = triangledFaceTextureVertexIndices;
    this->triangledFaceVertexIndices = triangledFaceVertexIndices;
}

void Model::calculateNewNormals()
{
    TranformationsForModel::calculateNormals(
                this->normalsForVertices, this->triangledFaceVertexIndices, this->vertices);
}
