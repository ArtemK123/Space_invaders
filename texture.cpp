#include "texture.h"

Texture::Texture(int x, int y) :
    Object(x, y),
    Drawable_Object (x, y)
{
    this->m_width = 44;
    this->m_height = 32;
    this->m_x_blocks = 4;
    this->m_y_blocks = 4;
    this->m_block_width = m_width / m_x_blocks;
    this->m_block_height = m_height / m_y_blocks;
    QPixmap sprite_sheet(":/sources/sprite_sheet.png");
    m_image = unique_ptr<QPixmap>(new QPixmap(sprite_sheet.copy(316, 213, 44, 32)));
    this->m_matrix = new int*[static_cast<size_t>(m_x_blocks)];
    for (int i = 0; i < m_x_blocks; i++) {
        this->m_matrix[i] = new int[static_cast<size_t>(m_y_blocks)];
    }
    this->refill();
}

void Texture::refill() {
    for (int i = 0; i < m_x_blocks; i++) {
        for (int j = 0; j < m_y_blocks; j++) {
            m_matrix[i][j] = 3;
        }
    }
}

bool Texture::checkHit(shared_ptr<Bullet> bullet) {
    if (bullet->checkObjectCollision(*this))
    {
        Object* test_block = new Object(m_x, m_y);
        test_block->setSize(m_block_width, m_block_height);
        for (int i = 0; i < m_x_blocks; i++) {
            for (int j = 0; j < m_y_blocks; j++) {
                if (m_matrix[i][j] > 0) {
                    test_block->setX(m_x + i * m_block_width);
                    test_block->setY(m_y + j * m_block_height);
                    if (bullet->checkObjectCollision(*test_block)) {
                        m_matrix[i][j]--;
                        delete test_block;
                        return true;
                    }
                }
            }
        }
        delete test_block;
    }
    return false;
}


QPixmap Texture::getPicture(int i, int j) {
    QPixmap image = m_image->copy(i * m_block_width, j * m_block_height, m_block_width, m_block_height);
    return image;
}

void Texture::draw(QPainter& painter) {
    for (int i = 0; i < m_x_blocks; i++) {
        for (int j = 0; j < m_y_blocks; j++) {
            if (m_matrix[i][j] != 0) {
                QPixmap image = getPicture(i, j);
                painter.drawPixmap(m_x + i * m_block_width, m_y + j * m_block_height, image);
            }
        }
    }
}

Texture::~Texture() {
    for (int i = 0; i < m_x_blocks; i++) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}
