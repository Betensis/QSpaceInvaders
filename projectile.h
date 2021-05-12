#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QImage>
#include <QPainter>


enum projectileMoveDirections {
    UP,
    DOWN
};

class Projectile
{
public:
    Projectile(QImage image, QSize size, int speed, QPoint coord, int moveDirection = projectileMoveDirections::DOWN);
    void move();
    void draw(QPainter *painter);
    QPoint getCoord() const;

    QSize getSize() const;
    void setSize(const QSize &value);

private:
    QImage image;
    QSize size;
    int speed;
    QPoint coord;
    int moveDirection;
};

class ProjectileFactory
{
public:
    ProjectileFactory(QImage image, QSize prjSize, int speed, int moveDirection = projectileMoveDirections::DOWN);
    Projectile getProjectile(QPoint projCoord);

    QSize getPrjSize() const;

private:
    QImage image;
    QSize prjSize;
    int speed;
    int moveDirection;
};



#endif // PROJECTILE_H
