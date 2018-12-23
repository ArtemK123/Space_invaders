#include "units.h"

Enemy::Enemy(int x, int y, int dx, int dy)
    : Animated_Object(x, y),
      Movable_Object(x, y, dx ,dy),
      Dying(),
      Scored()
{

}

void Enemy::kill() {
    m_dying = true;
    m_current_image = 0;
}

void Enemy::animate() {
    if (!is_dying()) {
        m_current_image = (m_current_image >= static_cast<int>(m_images.size()) - 1) ? 0 : m_current_image + 1;
    }
    else if (is_dying()) {
        if (m_current_image == static_cast<int>(m_dying_images.size()) - 1) {
            m_dead = true;
        }
        else {
            m_current_image++;
        }
    }
}

void Enemy::draw(QPainter& painter) {
    if (!is_dying()) {
        painter.drawPixmap(m_x, m_y, *m_images[static_cast<unsigned long long>(m_current_image)]);
    }
    else if (is_dying()) {
        painter.drawPixmap(m_x, m_y, *m_dying_images[static_cast<unsigned long long>(m_current_image)]);
    }
}

Enemy::~Enemy() {

}

Enemy_1::Enemy_1(int x, int y, int dx, int dy)
    : Object(x, y),
      Enemy(x, y, dx, dy)
{
    this->m_width = 17;
    this->m_height = 16;
    this->m_points = 40;
    QPixmap sprite_sheet(":/sources/sprite_sheet.png");
    QPixmap image1 = sprite_sheet.copy(6, 225, 17, 16);
    QPixmap image2 = sprite_sheet.copy(39, 225, 17, 16);
    m_images.push_back(unique_ptr<QPixmap>(new QPixmap(image1)));
    m_images.push_back(unique_ptr<QPixmap>(new QPixmap(image2)));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(443, 280, 14, 8))));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(441, 278, 18, 12))));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(437, 276, 26, 16))));
    m_current_image = 0;
}

shared_ptr<Bullet> Enemy_1::shoot() {
    return shared_ptr<Bullet>(new Enemy_Bullet(m_x + m_width / 2, m_y + m_height, 0, abs(this->m_dx) * 2));
}

Enemy_1::~Enemy_1() {

}

Enemy_2::Enemy_2(int x, int y, int dx, int dy)
    : Object(x, y),
      Enemy(x, y, dx, dy)
{
    this->m_width = 23;
    this->m_height = 16;
    this->m_points = 20;
    QPixmap sprite_sheet(":/sources/sprite_sheet.png");
    QPixmap image1 = sprite_sheet.copy(106, 225, 23, 16);
    QPixmap image2 = sprite_sheet.copy(73, 225, 23, 16);
    m_images.push_back(unique_ptr<QPixmap>(new QPixmap(image1)));
    m_images.push_back(unique_ptr<QPixmap>(new QPixmap(image2)));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(443, 280, 14, 8))));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(441, 278, 18, 12))));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(437, 276, 26, 16))));
    m_current_image = 0;
}

shared_ptr<Bullet> Enemy_2::shoot() {
    return shared_ptr<Bullet>(new Enemy_Bullet(m_x + m_width / 2, m_y + m_height, 0, abs(this->m_dx) * 2));
}

Enemy_2::~Enemy_2() {

}

Enemy_3::Enemy_3(int x, int y, int dx, int dy)
    : Object(x, y),
      Enemy(x, y, dx, dy)
{
    this->m_width = 23;
    this->m_height = 16;
    this->m_points = 10;
    QPixmap sprite_sheet(":/sources/sprite_sheet.png");
    QPixmap image1 = sprite_sheet.copy(146, 226, 23, 16);
    QPixmap image2 = sprite_sheet.copy(178, 226, 23, 16);
    m_images.push_back(unique_ptr<QPixmap>(new QPixmap(image1)));
    m_images.push_back(unique_ptr<QPixmap>(new QPixmap(image2)));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(443, 280, 14, 8))));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(441, 278, 18, 12))));
    m_dying_images.push_back(unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(437, 276, 26, 16))));
    m_current_image = 0;
}

shared_ptr<Bullet> Enemy_3::shoot() {
    return shared_ptr<Bullet>(new Enemy_Bullet(m_x + m_width / 2, m_y + m_height, 0, abs(this->m_dx) * 2));
}

Enemy_3::~Enemy_3() {

}

Ufo::Ufo(int x, int y, int dx, int dy)
    : Object(x, y),
      Movable_Object(x, y, dx, dy),
      Dying(),
      Scored()
{
    m_width = 49;
    m_height = 22;
    QPixmap sprite_sheet(":/sources/sprite_sheet.png");
    m_image = unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(214, 223, 49, 22)));
    int points[] = {10, 50, 100, 500};
    m_points = points[rand() % 4];
}

void Ufo::kill() {
    m_dead = true;
    m_dying = true;
}

Ufo::~Ufo() {

}

Player::Player(int x, int y, int speed)
    : Object(x, y),
      Drawable_Object(x, y),
      Movable_Object(x, y, speed, 0),
      Dying()
{
    m_width = 26;
    m_height = 16;
    m_dead = false;
    QPixmap sprite_sheet(":/sources/sprite_sheet.png");
    QPixmap image1 = sprite_sheet.copy(277, 228, 26, 16);
    QPixmap image2 = sprite_sheet.copy(367, 275, 26, 16);
    m_image = unique_ptr<QPixmap>(new QPixmap(image1));
    m_dead_image = unique_ptr<QPixmap>(new QPixmap(image2));
    m_frame_count = 0;
}

void Player::kill() {
    if (m_frame_count == 0) {
        m_frame_count = 60;
        m_dying = true;
    }
}

void Player::relive() {
    this->m_frame_count = 0;
    this->m_dead = false;
    this->m_dying = false;
}

QPixmap Player::getDefaultPicture() {
    return *m_image;
}

void Player::draw(QPainter& painter) {
    if (!m_dying) {
        painter.drawPixmap(m_x, m_y, *m_image);
    }
    else if (m_frame_count > 0) {
        m_frame_count--;
        if (m_frame_count / 10 % 2 == 0) {
            painter.drawPixmap(m_x, m_y, *m_image);
        }
        else if (m_frame_count / 10 % 2 == 1) {
            painter.drawPixmap(m_x, m_y, *m_dead_image);
        }
    }
    else if (m_frame_count == 0) {
        m_dead = true;
        painter.drawPixmap(m_x, m_y, *m_dead_image);
    }
}

shared_ptr<Bullet> Player::shoot() {
    return shared_ptr<Bullet>(new Player_Bullet(m_x + m_width / 2, m_y, 0, abs(m_dx) * -2));
}

Player::~Player() {

}
