#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <iostream>
#include <random>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , timer(new QTimer(this))
    , resetTimer(new QTimer(this))
    , maxRows(150)
    , minRows(3)
    , trailSquareNumber(30)
    , mazeColor(QColor (220, 220, 220))
    , squareColor(QColor (0, 255, 255))

    , mazeRows(20)
    , delay(50)

    , topHeight(80)

    ,hasSetUiDimensions(false)
{
    ui->setupUi(this);
    ui->mazeGraphicView->setScene(scene);

    connect(resetTimer, &QTimer::timeout, this, &MainWindow::autoReset);
    connect(timer, &QTimer::timeout, this, &MainWindow::destroyNextWall);
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::manualReset);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        qApp->quit();
    }
    else {
        QMainWindow::keyPressEvent(event);
    }
}

//this function automatically is called right after the screen has been set in fullscreen
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if(!hasSetUiDimensions){
        hasSetUiDimensions = true;

        setUIDimensions();
        createMaze();
    }
}


void MainWindow::setUIDimensions(){
    windowSize = size();
    graphicViewWidth = windowSize.width();
    graphicViewHeight = windowSize.height() - topHeight;
    QGraphicsView *mazeGraphicView = findChild<QGraphicsView*>("mazeGraphicView");
    QPushButton *createButton = findChild<QPushButton*>("createButton");

    QLineEdit *mazeRowsLineEdit = findChild<QLineEdit*>("mazeRowsLineEdit");
    QLabel *mazeRowsLabel = findChild<QLabel*>("mazeRowsLabel");
    QLineEdit *delayLineEdit = findChild<QLineEdit*>("delayLineEdit");
    QLabel *delayLabel = findChild<QLabel*>("delayLabel");

    mazeGraphicView->setFixedSize(graphicViewWidth, graphicViewHeight);
    mazeGraphicView->move(0, topHeight - 30);

    createButton->move(10, 5);

    mazeRowsLabel->move(120, 2);
    mazeRowsLineEdit->move(305, 1);
    delayLabel->move(120, 26);
    delayLineEdit->move(328, 25);

    ui->mazeRowsLineEdit->setText(QString("%1").arg(mazeRows));
    ui->delayLineEdit->setText(QString("%1").arg(delay));




}

void MainWindow::resetVariables(){
    backPath.clear();
    currentBoxCoordinates = {0,0};
    boxesInThePath = {{0,0}};
    generatorSquarePath = {{0,0}};
    completePath.clear();
    resetStep = 1;
}




void MainWindow::setSizes(){
    delay = ui->delayLineEdit->text().toInt();
    mazeRows = std::min(ui->mazeRowsLineEdit->text().toInt(),150);

    ui->mazeRowsLineEdit->setText(QString("%1").arg(mazeRows));
    ui->delayLineEdit->setText(QString("%1").arg(delay));

    wallHeight = std::round((graphicViewHeight) / mazeRows);
    wallWidth = 1;

    trueWallHeight = (wallHeight - wallWidth);

    startingXandY = {(graphicViewWidth - (trueWallHeight * mazeRows)) / 2,
                     ((graphicViewHeight) - (trueWallHeight * mazeRows)) / 2};

    trailSquareNumber = mazeRows * 2;
}


void MainWindow::createMaze(){

    resetVariables();

    setSizes();
    createSquares(startingXandY[0] + wallWidth,startingXandY[1] + wallWidth,wallHeight - 2 * wallWidth);
    drawGrid();
    walls[1]->setVisible(false);

    timer->start(delay);
}


void MainWindow::createWall(int x, int y, int width, int height){
    QGraphicsRectItem *wall = scene->addRect(x, y, width, height);

    wall->setPen(Qt::NoPen);
    wall->setBrush(mazeColor);
    wall->setZValue(trailSquareNumber + 2);

    walls.append(wall);
}

void MainWindow::createSquares(int x, int y, int width){

    //generator square
    generatorSquare = scene->addRect(x, y, width, width);
    generatorSquare->setBrush(squareColor);
    generatorSquare->setZValue(trailSquareNumber + 1);

    //trail squares
    for(int i = 0; i < trailSquareNumber; i++){
        QGraphicsRectItem *trailSquare = scene->addRect(x - wallWidth, y - wallWidth, width + 2 * wallWidth, width + 2 * wallWidth);

        trailSquare->setPen(Qt::NoPen);
        int colorByte = 160 - i*150/trailSquareNumber;
        trailSquare->setBrush(QColor (0, colorByte, colorByte));
        trailSquare->setZValue(trailSquareNumber-i);

        trailSquares.append(trailSquare);
    }
}

void MainWindow::manualReset(){
    resetTimer->stop();
    timer->stop();
    walls.clear();
    trailSquares.clear();
    scene->clear();
    createMaze();
}


void MainWindow::autoReset(){

    //smooth reset effect (square goes back, filling the maze)
    int n = completePath.length();
    currentBoxCoordinates = {completePath[n-resetStep][0], completePath[n-resetStep][1]};

    if(completePath[n-resetStep].length() == 3){
        walls[completePath[n-resetStep][2]]->setVisible(true);
    }
    moveSquares();
    resetStep++;

    if(resetStep >n){
        //automatic reset
        resetTimer->stop();
        resetVariables();
        timer->start(delay);
    }
}

void MainWindow::drawGrid(){

    for (int i = 0; i < mazeRows; ++i) {
        for (int j = 0; j < mazeRows; ++j) {
            createWall(startingXandY[0] + j * trueWallHeight, startingXandY[1] +  i * trueWallHeight, wallWidth, wallHeight); // left wall of each cell (vertical)
            createWall(startingXandY[0] + j * trueWallHeight, startingXandY[1] +  i * trueWallHeight, wallHeight, wallWidth); // top wall of each cell (horizontal)
        }
    }
    for (int i = 0; i < mazeRows; ++i) {
        createWall(startingXandY[0] + mazeRows * trueWallHeight, startingXandY[1] + i * trueWallHeight, wallWidth, wallHeight); //right wall of the grid (vertical)
    }

    for (int i = 0; i < mazeRows - 1; ++i) {//we dont want the last bottom wall because it is the end
        createWall(startingXandY[0] + i * trueWallHeight, startingXandY[1] + mazeRows * trueWallHeight, wallHeight, wallWidth); //bottom wall of the grid (horizontal)
    }

}

void MainWindow::destroyNextWall(){

    indexesThatCantBeDestroyed.clear();
    //{{wallIndex, boxCoordinate[0],boxCoordinate[1]}, ...}
    // i create a list of the 4 boxes near the current coordinates, with the index of the wall that we need to destroy to go to this near box
    closeWallsAndBoxesIndexes = { {currentBoxCoordinates[0] * 2 + 1 + currentBoxCoordinates[1] * mazeRows * 2, //top box
                                            currentBoxCoordinates[0], currentBoxCoordinates[1] - 1},

                                            {currentBoxCoordinates[0] * 2 + 2 + currentBoxCoordinates[1] * mazeRows * 2, // right box
                                            currentBoxCoordinates[0] + 1, currentBoxCoordinates[1]},

                                            {currentBoxCoordinates[0] * 2 + 1 + (currentBoxCoordinates[1] + 1) * mazeRows * 2, //bottom box
                                            currentBoxCoordinates[0], currentBoxCoordinates[1] + 1},

                                            {currentBoxCoordinates[0] * 2 + 0 + currentBoxCoordinates[1] * mazeRows * 2, // left box
                                            currentBoxCoordinates[0] - 1, currentBoxCoordinates[1]}
    };

    // remove the boxes that are out of bounds, if they have negative coordinates or beyond the rows of the grid
    // to do that i check if the current x coordinate is null or equal to mazerows - 1, same for y, and add the corresponding index to the list
    // 'indexesThatCantBeDestroyed', for example, if I add 0, to this list, that mean that the top wall cant be destroy bc it is out of bounds.
    // 'listOfCorrespondence' allow me not to make 4 if statement.

    QVector<QVector<int>> listOfCorrespondence = {{1,0,0},{0,mazeRows - 1,1},{1,mazeRows - 1,2},{0,0,3}};
    for(int i = 0; i < 4 ; i++){
        if(currentBoxCoordinates[listOfCorrespondence[i][0]] == listOfCorrespondence[i][1]){
            indexesThatCantBeDestroyed.append(listOfCorrespondence[i][2]);
        }
    }


    //check if any close box has already been in the path, i cant go to a box that i already crossed
    for(int i = 0; i < closeWallsAndBoxesIndexes.size() ; i++){
        for(int j = 0; j < boxesInThePath.size() ; j++){
            if(closeWallsAndBoxesIndexes[i][1] == boxesInThePath[j][0] && closeWallsAndBoxesIndexes[i][2] == boxesInThePath[j][1]){
                indexesThatCantBeDestroyed.append(i);
            }
        }
    }


    //destroy the boxes coord that i cant go to i sort it to remove the right indexes
    std::sort(indexesThatCantBeDestroyed.begin(), indexesThatCantBeDestroyed.end());
    for(int i = indexesThatCantBeDestroyed.size() - 1; i >= 0  ; i--){
        closeWallsAndBoxesIndexes.removeAt(indexesThatCantBeDestroyed[i]);
    }

    //if i can go somewhere, i choose between all possibilities randomly, and go there
    if(indexesThatCantBeDestroyed.size() != 4){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, closeWallsAndBoxesIndexes.size() - 1);

        QVector<int> choice = closeWallsAndBoxesIndexes[distrib(gen)];

        //unsee wall
        walls[choice[0]]->setVisible(false);

        completePath.append({currentBoxCoordinates[0], currentBoxCoordinates[1], choice[0]});

        currentBoxCoordinates = {choice[1], choice[2]};
        boxesInThePath.append(currentBoxCoordinates);
        backPath.append(currentBoxCoordinates);

    }

    //if not, i go back
    else{
        currentBoxCoordinates = backPath[backPath.size() - 2];
        backPath.removeAt(backPath.size() - 1);
        completePath.append({currentBoxCoordinates[0], currentBoxCoordinates[1]});
    }

    //if all boxes has been crossed then start automatic reset.
    if(boxesInThePath.size() == std::pow(mazeRows,2)){

        timer->stop();
        resetTimer->start(std::round(delay / 10));
        return;
    }

    moveSquares();
}

void MainWindow::moveSquares(){

    //squares are the generator square and its trail squares
    generatorSquare->setPos(currentBoxCoordinates[0] * trueWallHeight ,currentBoxCoordinates[1] * trueWallHeight );
    generatorSquarePath.append(currentBoxCoordinates);
    int n = generatorSquarePath.length();

    for(int i = 0; i < trailSquareNumber;i++){
        trailSquares[i]->setPos(generatorSquarePath[std::max(n-i-2, 0)][0] * (trueWallHeight),
                                generatorSquarePath[std::max(n-i-2, 0)][1] * (trueWallHeight));
    }
}

















