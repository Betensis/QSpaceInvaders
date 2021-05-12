#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QImage>
#include <QPainter>
#include <projectile.h>


class Spaceship
{
public:
    Spaceship(const QImage &image, ProjectileFactory *projectileFactory, int speed, QSize shipSize = QSize(65, 65));
    void setStartPosition(QPoint coord);
    void draw(QPainter *painter);
    void move(int moveDirection);
    Projectile shoot();
    enum moveDirections {
        LEFT,
        RIGHT,
        STOP
    };
    QPoint getPositionsCoord() const;
    QSize getShipSize() const;
    bool isIntersection(Projectile prj);
protected:
    QPoint positionsCoord = QPoint(1, 1);
    QImage image;
    ProjectileFactory *projectileFactory;
    int speed;
    QSize shipSize;
};

#endif // SPACESHIP_H
