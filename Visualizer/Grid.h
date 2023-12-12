#pragma once
class Grid
{
public:
    Grid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float gridSize);
    ~Grid();
private:
    void storeGrid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float gridSize);
};
