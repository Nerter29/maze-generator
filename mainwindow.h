#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsitem.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTimer *resetTimer;


    QGraphicsRectItem *generatorSquare;
    QVector<QGraphicsRectItem*> trailSquares;
    int trailSquareNumber;
    QVector<QVector<int>> generatorSquarePath;
    QVector<QGraphicsRectItem*> solvingPath;
    QVector<QGraphicsRectItem*> walls;
    QVector<QVector<int>> boxesInThePath;
    QVector<QVector<int>> backPath;
    QVector<QVector<int>> completePath;

    QVector<int> currentBoxCoordinates;
    QVector<QVector<int>> closeWallsAndBoxesIndexes;
    QVector<int> indexesThatCantBeDestroyed = {};

    int wallHeight;
    int wallWidth;
    int trueWallHeight;
    QColor mazeColor;
    QColor squareColor ;

    QVector<int> startingXandY;
    int mazeRows;
    int maxRows;
    int minRows;
    int delay;
    int resetStep;

    QSize windowSize;
    int graphicViewWidth;
    int graphicViewHeight;
    int topHeight;

    bool hasSetUiDimensions;


    void setSizes();
    void setUIDimensions();
    void resizeEvent(QResizeEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void drawGrid();
    void createSquares(int x, int y, int width);

    void createWall(int x, int y, int width, int height);
    void createMaze();
    void destroyNextWall();

    void autoReset();
    void moveSquares();
    void resetVariables();
    void manualReset();







};
#endif // MAINWINDOW_H
