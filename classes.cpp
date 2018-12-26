#include "classes.h"

Object::Object(int x, int y) {
    this->m_x = x;
    this->m_y = y;
}

int Object::getX() {
    return this->m_x;
}

void Object::setX(int val) {
    this->m_x = val;
}

int Object::getY() {
    return this->m_y;
}

void Object::setY(int val) {
    this->m_y = val;
}

int Object::getWidth() {
    return this->m_width;
}

int Object::getHeight() {
    return this->m_height;
}

void Object::setSize(int width, int height) {
    if (width > 0 && height > 0) {
        m_width = width;
        m_height = height;
    }
    else {
        throw string("Bad size for object");
    }
}

Object::~Object() {

}

Drawable_Object::Drawable_Object(int x, int y) :
    Object(x, y)
{
    m_image = nullptr;
}

void Drawable_Object::draw(QPainter& painter) {
    painter.drawPixmap(m_x, m_y, *m_image);
}

Drawable_Object::~Drawable_Object() {

}

Animated_Object::Animated_Object(int x, int y)
    : Object(x, y)
{
    this->m_images = vector<unique_ptr<QPixmap>>();
    this->m_current_image = 0;
}

void Animated_Object::animate() {
    m_current_image = (m_current_image == static_cast<int>(m_images.size()) - 1) ? 0 : m_current_image + 1;
}

void Animated_Object::draw(QPainter& painter) {
    painter.drawPixmap(m_x, 384 - m_height - m_y, *m_images[static_cast<unsigned long long>(m_current_image)]);
}

Animated_Object::~Animated_Object() {

}


Movable_Object::Movable_Object(int x, int y, int dx, int dy)
    : Object(x, y)
{
    m_dx = dx;
    m_dy = dy;
}

bool Movable_Object::checkMapCollision(int map_width, int map_height) {
    if (m_x <= 0 || m_x + m_width >= map_width ||
        m_y <= 0 || m_y + m_height >= map_height)
    {
        return true;
    }
    else {
        return false;
    }
}

bool Movable_Object::checkObjectCollision(Object& object) {
    if (    m_x > object.getX() + object.getWidth() ||
            m_x + m_width < object.getX() ||
            m_y > object.getY() + object.getHeight() ||
            m_y + m_height < object.getY())
    {
        return false;
    }
    else {
        return true;
    }
}

void Movable_Object::move() {
    m_x += m_dx;
    m_y += m_dy;
}

void Movable_Object::moveBack() {
    m_x -= m_dx;
    m_y -= m_dy;
}

int Movable_Object::getDx() {
    return m_dx;
}

int Movable_Object::getDy() {
    return m_dy;
}

void Movable_Object::setSpeed(int dx, int dy) {
    m_dx = dx;
    m_dy = dy;
}

Movable_Object::~Movable_Object() {

}

Dying::Dying() {
    m_dying = false;
    m_dead = false;
}

bool Dying::is_dying() {
    return m_dying;
}

bool Dying::is_dead() {
    return m_dead;
}

void Dying::kill() {
    m_dying = true;
}

Dying::~Dying() {

}

Scored::Scored(int points) {
    m_points = points;
}

int Scored::getPoints() {
    return m_points;
}

Scored::~Scored() {

}
