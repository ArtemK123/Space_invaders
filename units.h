#ifndef UNITS_H
#define UNITS_H

#include "classes.h"
#include "bullets.h"

class Enemy : public Animated_Object, public Movable_Object, public Dying, public Scored, public IShooting {
protected:
    vector<unique_ptr<QPixmap>> m_dying_images;
public:
    virtual shared_ptr<Bullet> shoot() override = 0;
    void animate() override;
    void draw(QPainter& painter) override;
    void kill() override;

    Enemy(int x, int y, int dx, int dy);
    ~Enemy() override;
};

class Enemy_1 : public Enemy {
public:
    Enemy_1(int x, int y, int dx, int dy);
    shared_ptr<Bullet> shoot() override;
    ~Enemy_1() override;
};


class Enemy_2 : public Enemy {
public:
    Enemy_2(int x, int y, int dx, int dy);
    shared_ptr<Bullet> shoot() override;
    ~Enemy_2() override;
};

class Enemy_3 : public Enemy {
public:
    Enemy_3(int x, int y, int dx, int dy);
    shared_ptr<Bullet> shoot() override;
    ~Enemy_3() override;
};

class Ufo : public Drawable_Object, public Movable_Object, public Dying, public Scored, public ILogic {
protected:
    int m_frame_count;

public:
    void kill() override;
    void update() override;
    Ufo(int x, int y, int dx, int dy = 0);
    ~Ufo() override;
};

class Player : public Drawable_Object, public Movable_Object, public Dying, public IShooting, public ILogic {
protected:
    unique_ptr<QPixmap> m_dead_image;
    int m_frame_count;

public:
    void relive();
    void kill() override;
    void draw(QPainter& painter) override;
    void update() override;

    QPixmap getDefaultPicture();
    shared_ptr<Bullet> shoot() override;

    Player(int x, int y, int speed);
    ~Player() override;
};

#endif // UNITS_H
