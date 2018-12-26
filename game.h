#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "classes.h"
#include "texture.h"
#include "bullets.h"
#include "units.h"
#include "sound.h"
#include <QKeyEvent>
#include <iostream>
#include "record_file.h"

class Game {
protected:
    vector<shared_ptr<Enemy>> m_enemies;
    shared_ptr<Ufo> m_ufo;
    vector<shared_ptr<Texture>> m_textures;
    unique_ptr<Sound_Manager> m_sound_manager;
    unique_ptr<Player> m_player;

    shared_ptr<Bullet> m_player_bullet;
    vector<shared_ptr<Bullet>> m_enemy_bullets;    
    shared_ptr<Pressed_Buttons> m_buttons;
    QObject* m_parent;

    const string source_path = "./../Space_invaders/sources";

    int m_score;
    int m_highscore;
    int m_frame_count;
    int m_speed;
    int m_lives;
    int m_difficult;
    bool m_endgame;
    bool m_is_pause;

    void printNumber(int value, int start_x, int start_y, QPainter& painter);
    void printScore(QPainter& painter);
    void printTitle(QPainter& painter);
    void readHighScore();
    void create_enemies();
    void create_textures();
    void updatePlayer();
    void updatePlayerBullet();
    void updateEnemies();
    void updateEnemyBullets();
    void updateUfo();
    void checkDifficult();

public:
    const int m_board_width = 600;
    const int m_board_height = 600;

    bool is_endgame();
    void start();
    void pause();
    void update();
    int getScore();
    void mute();
    void unmute();
    bool is_muted();
    void endgame();
    void draw(QPainter& painter);

    Game(shared_ptr<Pressed_Buttons> buttons, QObject* parent);
    ~Game();
};

#endif // GAME_H
