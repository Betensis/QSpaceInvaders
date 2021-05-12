#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainWindowSize = QSize(1080, 720);
    setFixedSize(mainWindowSize);
    userSpaceship.setStartPosition(QPoint(
                                       (mainWindowSize.width() - spaceshipSize.width()) * 0.5,
                                       mainWindowSize.height() - spaceshipSize.height()));

    addEnemySpaceship(1);
    projectileTimer = new QTimer(this);
    connect(projectileTimer, SIGNAL(timeout()), this, SLOT(moveProjectiles()));
    projectileTimer->start(50);

    enemyMoveTimer = new QTimer(this);
    connect(enemyMoveTimer, SIGNAL(timeout()), this, SLOT(moveEnemySpaceship()));
    enemyMoveTimer->start(enemyMoveInterval);

    shootEnemyTimer = new QTimer(this);
    connect(shootEnemyTimer, SIGNAL(timeout()), this, SLOT(shootRandomEnemySpaceship()));
    shootEnemyTimer->start(enemyShootInterval);

    srand(time(0));
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete shootEnemyTimer;
    delete enemyMoveTimer;
    delete projectileTimer;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (int i = 0; i < userProjectilesList.length(); i++) {
        userProjectilesList[i].draw(&painter);
    }
    for (int i = 0; i < enemyProjectileList.length(); i++) {
        enemyProjectileList[i].draw(&painter);
    }
    if (userHelth > 0){
        userSpaceship.draw(&painter);
    }
    else {
        endGame = true;
    }
    for (int i = 0; i < enemySpaceshipsList.length(); ++i) {
        enemySpaceshipsList[i].draw(&painter);
    }


}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key()) {
    case Qt::Key_Left:
        if (userSpaceship.getPositionsCoord().x() > 0)
            userSpaceship.move(Spaceship::LEFT);
        break;
    case Qt::Key_Right:
        if (userSpaceship.getPositionsCoord().x() + spaceshipSize.width() < mainWindowSize.width())
            userSpaceship.move(Spaceship::RIGHT);
        break;
    case Qt::Key_Space:
        userProjectilesList.append(userSpaceship.shoot());
        break;
    }
    repaint();
}

void MainWindow::rewriteScore()
{
    ui->scoreLable->setText(QString("Score: ") + QString::number(scoreInfo));
}

void MainWindow::rewriteHealpoint()
{
    ui->healpointLabel->setText(QString("Healpoint: ") + QString::number(userHelth));
}

void MainWindow::setEnemyShootInterval(int value)
{
    enemyShootInterval = value;
    shootEnemyTimer->setInterval(value);
}

void MainWindow::setEnemyMoveInterval(int value)
{
    enemyMoveInterval = value;
    enemyMoveTimer->setInterval(enemyMoveInterval);
}

void MainWindow::addEnemySpaceship(int lines)
{
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < 6; ++j) {
            enemySpaceshipsList.append(Spaceship(enemyImage, &enemyProjectileFactory, projectileSpeed, spaceshipSize));
            enemySpaceshipsList.back().setStartPosition(QPoint((mainWindowSize.width() / 8) * j  + 100,
                                                               infotableOffset.height() + (spaceshipSize.height() + 25) * i));
        }
    }
}

void MainWindow::shootRandomEnemySpaceship()
{
    if (endGame)
        return;
    if (! enemySpaceshipsList.isEmpty())
    {
        int randIndex = rand() % enemySpaceshipsList.length();

        enemyProjectileList.append(enemySpaceshipsList[randIndex].shoot());
    }
}


void MainWindow::moveEnemySpaceship()
{
    if (endGame)
        return;
    if (!enemySpaceshipsList.isEmpty()){
        int leftestEnemyXCoord = mainWindowSize.width() + 1;
        int rightestEnemyXCoord = -1;
        for (auto enemySpaceship : enemySpaceshipsList) {
            if (enemySpaceship.getPositionsCoord().x() < leftestEnemyXCoord)
                leftestEnemyXCoord = enemySpaceship.getPositionsCoord().x();
            if (enemySpaceship.getPositionsCoord().x() > rightestEnemyXCoord)
                rightestEnemyXCoord = enemySpaceship.getPositionsCoord().x();
        }
        switch (enemyMoveDirection) {
        case Spaceship::LEFT:
            if (leftestEnemyXCoord <= 70)
            {
                enemyMoveDirection = Spaceship::RIGHT;
            }
            break;
        case Spaceship::RIGHT:
            if (rightestEnemyXCoord >= mainWindowSize.width() - 70)
            {
                enemyMoveDirection = Spaceship::LEFT;
            }
            break;
        }
    }
    for (int i = 0; i < enemySpaceshipsList.length(); ++i) {
        enemySpaceshipsList[i].move(enemyMoveDirection);
    }
}

void MainWindow::moveProjectiles()
{
    if (endGame)
        return;
    for (int i = 0; i < userProjectilesList.length(); i++) {
        userProjectilesList[i].move();
        if (userProjectilesList[i].getCoord().y() + userProjectilesList[i].getSize().height() <= 0){
            userProjectilesList.removeAt(i);
        }
    }
    for (int i = 0; i < enemyProjectileList.length(); i++) {
        enemyProjectileList[i].move();
        if (enemyProjectileList[i].getCoord().y() - enemyProjectileList[i].getSize().height() >= mainWindowSize.height()){
            enemyProjectileList.removeAt(i);
        }
    }
    for (int i = 0; i < enemySpaceshipsList.length(); ++i) {
        for (int j = 0; j < userProjectilesList.length(); ++j) {
            if (enemySpaceshipsList[i].isIntersection(userProjectilesList[j]))
            {
                userProjectilesList.removeAt(j);
                enemySpaceshipsList.removeAt(i);
                scoreInfo += 100;
                rewriteScore();

                if (enemySpaceshipsList.isEmpty())
                {
                    if (enemySpaceshipLines < 3)
                        enemySpaceshipLines += 1;
                    addEnemySpaceship(enemySpaceshipLines);
                    if (enemyMoveInterval > 50)
                        setEnemyMoveInterval(enemyMoveInterval / 1.5);
                    setEnemyShootInterval(enemyShootInterval / 1.5);
                }
                return;
            }
        }
    }
    for (int i = 0; i < enemyProjectileList.length(); ++i) {
        if (userSpaceship.isIntersection(enemyProjectileList[i]))
        {
            userHelth -= 1;
            enemyProjectileList.removeAt(i);
            rewriteHealpoint();
            break;
        }
    }
    repaint();
}

