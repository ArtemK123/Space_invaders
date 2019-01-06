#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "base_classes.h"
#include "texture.h"
#include "bullets.h"
#include "units.h"
#include "sound.h"
#include <QKeyEvent>
#include "record_file.h"

class Game {
protected:
    vector<shared_ptr<Enemy>> m_enemies;
    shared_ptr<Ufo> m_ufo;
    vector<shared_ptr<Texture>> m_textures;
    unique_ptr<Sound_Manager> m_sound_manager;
    shared_ptr<Player> m_player;

    shared_ptr<Bullet> m_player_bullet;
    vector<shared_ptr<Bullet>> m_enemy_bullets;    
    shared_ptr<Pressed_Buttons> m_buttons;
    QObject* m_parent;

    vector<shared_ptr<ILogic>> m_toUpdate;
    vector<shared_ptr<IDrawable>> m_toDraw;

    string m_source_path;

    int m_score;
    int m_highscore;
    int m_frame_count;
    int m_speed;
    int m_lives;
    int m_difficult;
    bool m_endgame;
    bool m_pause;

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
    const int m_line_y = 540;

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

    Game(QObject* parent, shared_ptr<Pressed_Buttons> buttons, string source_path);
    ~Game();
};

#endif // GAME_H
