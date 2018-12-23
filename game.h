#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "classes.h"
#include "texture.h"
#include "bullets.h"
#include "units.h"
#include <QKeyEvent>
#include <iostream>

class Game {
public:
    const int m_board_width = 600;
    const int m_board_height = 600;
    vector<shared_ptr<Enemy>> m_enemies;
    shared_ptr<Ufo> m_ufo;
    vector<shared_ptr<Texture>> m_textures;
    shared_ptr<Player> m_player;
    Pressed_Buttoms m_buttoms;

    shared_ptr<Bullet> m_player_bullet;
    vector<shared_ptr<Bullet>> m_enemy_bullets;

    int m_score;
    int m_frame_count;
    int m_speed;
    int m_lives;
    bool m_endgame;
    bool m_is_pause;

    bool is_endgame();
    void start();
    void pause();
    void create_enemies();
    void create_textures();
    void updatePlayer();
    void updatePlayerBullet();
    void updateEnemies();
    void updateEnemyBullets();
    void update();
    void draw(QPainter& painter);
    void printScore(QPainter& painter);

    Game();
    ~Game();

};

#endif // GAME_H
