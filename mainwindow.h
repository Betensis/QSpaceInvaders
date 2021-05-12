#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define ll long long

#include "spaceship.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <QLabel>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *ev);


private:
    Ui::MainWindow *ui;
    QSize mainWindowSize;
    QSize infotableOffset = QSize(mainWindowSize.width(), 100);
    ll scoreInfo = 0;

    QTimer *projectileTimer;
    QTimer *enemyMoveTimer;
    QTimer *shootEnemyTimer;

    QSize projectileSize = QSize(15, 30);
    int projectileSpeed = 5;
    QSize spaceshipSize = QSize(60, 60);

    int userHelth = 5;
    int userSpaceshipSpeed = 10;
    ProjectileFactory userProjectileFactory =
            ProjectileFactory(QImage(":/missile.png"),
                              projectileSize,
                              projectileSpeed,
                              projectileMoveDirections::UP);
    QList<Projectile> userProjectilesList;
    Spaceship userSpaceship =  Spaceship(
                QImage(":/ship.bmp"),
                &userProjectileFactory,
                userSpaceshipSpeed,
                spaceshipSize);


    ProjectileFactory enemyProjectileFactory =
            ProjectileFactory(QImage(":/bomb.png"),
                              projectileSize,
                              projectileSpeed,
                              projectileMoveDirections::DOWN);
    QList<Projectile> enemyProjectileList;
    QList<Spaceship> enemySpaceshipsList;
    QImage enemyImage = QImage(":/alien.bmp");
    int enemyMoveDirection = Spaceship::RIGHT;
    int enemyMoveInterval = 500;
    int enemySpaceshipLines = 1;
    int enemyShootInterval = 5000;

    bool endGame = false;
    void rewriteScore();
    void rewriteHealpoint();
    void addEnemySpaceship(int lines);
    void setEnemyShootInterval(int value);
    void setEnemyMoveInterval(int value);
private slots:
    void shootRandomEnemySpaceship();
    void moveEnemySpaceship();
    void moveProjectiles();
};
#endif // MAINWINDOW_H
