#ifndef TEXTURE_H
#define TEXTURE_H

#include "base_classes.h"
#include "bullets.h"

class Texture : public Drawable_Object {
protected:
    int** m_matrix;
    int m_y_blocks;
    int m_x_blocks;
    int m_block_width;
    int m_block_height;

public:
    void draw(QPainter& painter) override;
    void refill();
    QPixmap getPicture(int i, int j);
    bool checkHit(shared_ptr<Bullet> bullet);
    Texture(int x, int y);
    ~Texture() override;
};

#endif // TEXTURE_H
