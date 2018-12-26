#include "bullets.h"

Bullet::Bullet(int x, int y, int dx, int dy)
    : Object(x, y),
      Movable_Object(x, y, dx, dy),
      Drawable_Object(x, y)
{

}

Bullet::~Bullet() {

}

Enemy_Bullet::Enemy_Bullet(int x, int y, int dx, int dy)
    : Object(x, y),
      Bullet(x, y, dx, dy)
{
    this->m_width = 6;
    this->m_height = 12;
    QPixmap sprite_sheet(":/sources/images/sprite_sheet.png");
    m_image = unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(413, 277, 6, 12)));
}

Enemy_Bullet::~Enemy_Bullet() {

}

Player_Bullet::Player_Bullet(int x, int y, int dx, int dy)
    : Object(x, y),
      Bullet(x, y, dx, dy)
{
    this->m_width = 2;
    this->m_height = 12;
    QPixmap sprite_sheet(":/sources/images/sprite_sheet.png");
    m_image = unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(415, 277, 2, 12)));
}

Player_Bullet::~Player_Bullet() {

}
