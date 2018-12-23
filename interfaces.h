#ifndef INTERFACES_H
#define INTERFACES_H

#include <QWidget>
#include <memory>
using namespace std;

class Object;
class Bullet;

class IMovable {
public:
    virtual void move() = 0;
    virtual void moveBack() = 0;
    virtual void setSpeed(int dx, int dy) = 0;
    virtual int getDx() = 0;
    virtual int getDy() = 0;
    virtual bool checkMapCollision(int map_width, int map_height) = 0;
    virtual bool checkObjectCollision(Object& object) = 0;
    virtual ~IMovable() = default;
};

class IDrawable {
public:
    virtual void draw(QPainter& painter) = 0;
    virtual ~IDrawable() = default;
};

class IAnimated {
public:
    virtual void animate() = 0;
    virtual ~IAnimated() = default;
};

class IDying {
public:
    virtual void kill() = 0;
    virtual bool is_dying() = 0;
    virtual bool is_dead() = 0;
    virtual ~IDying() = default;
};

class IShooting {
public:
    virtual shared_ptr<Bullet> shoot() = 0;
    virtual ~IShooting() = default;
};

class IScored {
public:
    virtual int getPoints() = 0;
    virtual ~IScored() = default;
};

#endif // INTERFACES_H
