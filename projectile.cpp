#include "projectile.h"

Projectile::Projectile(QImage image, QSize size, int speed, QPoint coord, int moveDirection)
    :image(image), size(size), speed(speed), coord(coord), moveDirection(moveDirection)
{

}

void Projectile::move()
{
    switch (moveDirection) {
    case UP:
        coord = QPoint(coord.x(), coord.y() - speed);
        break;
    case DOWN:
        coord = QPoint(coord.x(), coord.y() + speed);
        break;
    }
}

void Projectile::draw(QPainter *painter)
{
    painter->drawImage(QRect(coord, size),
                       image);
}

QPoint Projectile::getCoord() const
{
    return coord;
}

QSize Projectile::getSize() const
{
    return size;
}

void Projectile::setSize(const QSize &value)
{
    size = value;
}

ProjectileFactory::ProjectileFactory(QImage image, QSize prjSize, int speed, int moveDirection)
    :image(image), prjSize(prjSize), speed(speed), moveDirection(moveDirection)
{

}

Projectile ProjectileFactory::getProjectile(QPoint projCoord)
{
    return Projectile(image, prjSize, speed, projCoord, moveDirection);
}

QSize ProjectileFactory::getPrjSize() const
{
    return prjSize;
}

