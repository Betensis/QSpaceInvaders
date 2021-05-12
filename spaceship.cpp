#include "spaceship.h"

Spaceship::Spaceship(const QImage &image, ProjectileFactory *projectileFactory, int speed, QSize shipSize)
    :image(image), projectileFactory(projectileFactory), speed(speed), shipSize(shipSize)
{

}

void Spaceship::setStartPosition(QPoint coord)
{
    positionsCoord = coord;
}

void Spaceship::draw(QPainter *painter)
{
    painter->drawImage(QRect(positionsCoord, shipSize), this->image);
}

void Spaceship::move(int moveDirection)
{
    switch (moveDirection) {
    case moveDirections::LEFT:
        positionsCoord = QPoint(positionsCoord.x() - speed, positionsCoord.y());
        break;
    case moveDirections::RIGHT:
        positionsCoord = QPoint(positionsCoord.x() + speed, positionsCoord.y());
        break;
    }
}

Projectile Spaceship::shoot()
{
    return projectileFactory->getProjectile(QPoint(
                                               positionsCoord.x() + (shipSize.width() - projectileFactory->getPrjSize().width()) * 0.5,
                                               positionsCoord.y()
                                               ));
}

QPoint Spaceship::getPositionsCoord() const
{
    return positionsCoord;
}

QSize Spaceship::getShipSize() const
{
    return shipSize;
}

bool Spaceship::isIntersection(Projectile prj)
{
    if (prj.getCoord().x() > positionsCoord.x() and  prj.getCoord().x() < positionsCoord.x() + shipSize.width()
            and prj.getCoord().y() > positionsCoord.y() and  prj.getCoord().y() < positionsCoord.y() + shipSize.height())
        return true;
    if (prj.getCoord().x() + prj.getSize().width() > positionsCoord.x() and  prj.getCoord().x() + prj.getSize().width() < positionsCoord.x() + shipSize.width()
            and prj.getCoord().y() > positionsCoord.y() and  prj.getCoord().y() < positionsCoord.y() + shipSize.height())
        return true;
    if (prj.getCoord().x() > positionsCoord.x() and  prj.getCoord().x() < positionsCoord.x() + shipSize.width()
         and prj.getCoord().y() + prj.getSize().height() > positionsCoord.y() and  prj.getCoord().y() + prj.getSize().height() < positionsCoord.y() + shipSize.height())
        return true;
    if (prj.getCoord().x() + prj.getSize().width() > positionsCoord.x() and  prj.getCoord().x() + prj.getSize().width() < positionsCoord.x() + shipSize.width()
            and prj.getCoord().y() + prj.getSize().height() > positionsCoord.y() and  prj.getCoord().y() + prj.getSize().height() < positionsCoord.y() + shipSize.height())
        return true;
    return false;
}
