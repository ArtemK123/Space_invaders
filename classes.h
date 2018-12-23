#ifndef CLASSES_H
#define CLASSES_H

#include <QWidget>
#include <QPainter>
//#include <vector>
#include "interfaces.h"


using namespace std;

struct Pressed_Buttoms
{
    bool left = false;
    bool right = false;
    bool space = false;
};


class Object {
protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

public:
    int getX();
    int getY();
    void setX(int val);
    void setY(int val);
    int getWidth();
    int getHeight();
    void setSize(int width, int height);

    Object(int x, int y);
    virtual ~Object();
};

class Movable_Object : public virtual Object, public IMovable {
protected:
    int m_dx;
    int m_dy;

public:
    bool checkMapCollision(int map_width, int map_height) override;
    bool checkObjectCollision(Object& object) override;
    void move() override;
    void moveBack() override;
    int getDx() override;
    int getDy() override;
    void setSpeed(int dx, int dy) override;

    Movable_Object(int x, int y, int dx = 0, int dy = 0);
    ~Movable_Object() override;
};

class Drawable_Object : public virtual Object, public IDrawable {
protected:
    unique_ptr<QPixmap> m_image;

public:
    void draw(QPainter& painter) override;

    Drawable_Object(int x = 0, int y = 0);
    ~Drawable_Object() override;
};

class Animated_Object : public virtual Drawable_Object, public IAnimated {
protected:
    vector<unique_ptr<QPixmap>> m_images;
    int m_current_image;

public:
    void animate() override;
    void draw(QPainter& painter) override;

    Animated_Object(int x, int y);
    ~Animated_Object() override;
};

class Dying : public IDying {
protected:
    bool m_dying;
    bool m_dead;

public:
    bool is_dying() override;
    bool is_dead() override;
    void kill() override;

    Dying();
    ~Dying() override;
};

class Scored : public IScored {
protected:
    int m_points;
public:
    int getPoints() override;
    Scored(int points = 0);
    ~Scored() override;
};

#endif // CLASSES_H
