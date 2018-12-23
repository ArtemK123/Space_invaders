#ifndef BULLETS_H
#define BULLETS_H

#include "classes.h"

class Bullet : public Movable_Object, public Drawable_Object {
public:
    Bullet(int x, int y, int dx, int dy);
    ~Bullet() override;
};

class Enemy_Bullet : public Bullet {
public:
    Enemy_Bullet(int x, int y, int dx, int dy);
    ~Enemy_Bullet() override;
};

class Player_Bullet : public Bullet {
public:
    Player_Bullet(int x, int y, int dx, int dy);
    ~Player_Bullet() override;
};

#endif // BULLETS_H
