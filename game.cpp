#include "game.h"
#include <fstream>

Game::Game(QObject* parent, shared_ptr<Pressed_Buttons> buttons, string source_path)
{
    m_parent = parent;
    m_frame_count = 0;
    m_speed = 5;
    m_lives = 3;
    m_score = 0;
    m_highscore = 0;
    m_endgame = false;
    m_source_path = source_path;

    m_player = shared_ptr<Player>(new Player(285, 500, m_speed));
    m_player_bullet = nullptr;
    m_ufo = nullptr;
    m_buttons = buttons;
    m_sound_manager = unique_ptr<Sound_Manager>(new Sound_Manager(m_parent, m_source_path + "sounds/"));
    m_sound_manager->play();
}

void Game::start() {
    m_enemies.clear();
    m_textures.clear();
    m_enemy_bullets.clear();
    create_enemies();
    create_textures();
    checkDifficult();
    m_frame_count = 0;
    m_score = 0;
    m_ufo = nullptr;
    m_endgame = false;
    m_lives = 3;
    m_player->relive();
    m_player->setX(285);
    m_pause = false;
    readHighScore();
}

void Game::pause() {
    m_pause = (m_pause) ? false : true;
}

void Game::create_enemies() {
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 13; j++) {
            m_enemies.push_back(shared_ptr<Enemy>(new Enemy_1(103 + j * 32, 100 + i * 30, m_speed, 0)));
        }
    }
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 13; j++) {
            m_enemies.push_back(shared_ptr<Enemy>(new Enemy_2(101 + j * 32, 100 + i * 30, m_speed, 0)));
        }
    }
    for (int i = 3; i < 5; i++) {
        for (int j = 0; j < 13; j++) {
            m_enemies.push_back(shared_ptr<Enemy>(new Enemy_3(100 + j * 32, 100 + i * 30, m_speed, 0)));
        }
    }
}

void Game::create_textures() {
    m_textures.push_back(shared_ptr<Texture>(new Texture(133, 450)));
    m_textures.push_back(shared_ptr<Texture>(new Texture(233, 450)));
    m_textures.push_back(shared_ptr<Texture>(new Texture(333, 450)));
    m_textures.push_back(shared_ptr<Texture>(new Texture(433, 450)));
}

int Game::getScore() {
    return m_score;
}

void Game::update() {
    if (!m_pause) {
        m_toDraw.clear();
        m_toUpdate.clear();

        updatePlayer();

        if (!m_player->is_dead()) {
            updatePlayerBullet();

            updateEnemies();
            checkDifficult();

            updateEnemyBullets();

            updateUfo();

            if (m_enemies.size() == 0) {
                create_enemies();
                m_lives++;
            }

            for (auto texture : m_textures) {
                m_toDraw.push_back(texture);
            }

            m_frame_count = (m_frame_count == 23) ? 0 : m_frame_count + 1;
        }

        else if (m_player->is_dead()) {
            m_lives--;
            if (m_lives == 0) {
                endgame();
            }
            else {
                m_player->relive();
            }
        }

        for (auto logical : m_toUpdate) {
            logical->update();
        }
    }
}

void Game::updatePlayer() {
    if (!m_player->is_dead() && !m_player->is_dying()) {
        if (!m_buttons->left && m_buttons->right) {
            m_player->setSpeed(m_speed, 0);
            m_player->move();
        }
        if (m_buttons->left && !m_buttons->right) {
            m_player->setSpeed(-m_speed, 0);
            m_player->move();
        }
        if (m_buttons->space && m_player_bullet == nullptr) {
            m_player_bullet = m_player->shoot();
            m_sound_manager->shoot();
        }
        if (m_player->checkMapCollision(m_board_width, m_board_height)) {
            m_player->moveBack();
        }
    }
    m_toDraw.push_back(m_player);
    m_toUpdate.push_back(m_player);
}

void Game::updatePlayerBullet() {
    if (m_player_bullet != nullptr) {
        if (!m_player->is_dying()) {
            m_player_bullet->move();
        }

        if (m_player_bullet->checkMapCollision(m_board_width, m_board_height)) {
            m_player_bullet = nullptr;
            return;
        }
        for (int i = 0; i < static_cast<int>(m_enemies.size()); i++) {
            shared_ptr<Enemy> enemy = m_enemies[static_cast<size_t>(i)];
            if (m_player_bullet && m_player_bullet->checkObjectCollision(*enemy)) {
                enemy->kill();
                m_sound_manager->enemyKill();
                m_player_bullet = nullptr;
                return;
            }
        }
        for (auto texture : m_textures) {
            if (texture->checkHit(m_player_bullet)) {
                m_player_bullet = nullptr;
                return;
            }
        }
        if (m_ufo && m_player_bullet->checkObjectCollision(*m_ufo)) {
            m_ufo->kill();
            m_sound_manager->ufoKill();
            m_player_bullet = nullptr;
            return;
        }
        m_toDraw.push_back(m_player_bullet);
    }
}

void Game::updateEnemies() {
    for (int i = 0; i < static_cast<int>(m_enemies.size()); i++) {
        shared_ptr<Enemy> enemy = m_enemies[static_cast<size_t>(i)];
        if (enemy->is_dead()) {
            m_score += enemy->getPoints();
            m_enemies.erase(m_enemies.begin() + i);
            i--;
            continue;
        }
        else if (enemy->is_dying()) {
            enemy->animate();
        }
    }
    int shooting_unit = -1;
    if (m_enemies.size() == 0) {
        shooting_unit = -1;
    }
    else if (m_difficult == 1) {
        shooting_unit = rand() % static_cast<int>((m_enemies.size() * 2));
    }
    else if (m_difficult == 2) {
        shooting_unit = rand() % static_cast<int>((m_enemies.size() * 2));
    }
    else if (m_difficult == 3) {
        shooting_unit = rand() % static_cast<int>((m_enemies.size() * 4));
    }
    bool on_edge = false;
    for (int i = 0; i < static_cast<int>(m_enemies.size()); i++) {
        shared_ptr<Enemy> enemy = m_enemies[static_cast<size_t>(i)];
        if (!enemy->is_dead()) {
            m_toDraw.push_back(enemy);
        }
        if (!enemy->is_dead() && !enemy->is_dying() && !m_player->is_dying()) {
            if ((m_difficult == 1 && m_frame_count % 12 == 0) ||
                (m_difficult == 2 && m_frame_count % 8 == 0) ||
                (m_difficult == 3 && m_frame_count % 6 == 0))
            {
                enemy->animate();
                enemy->move();
                m_sound_manager->background();
                if (enemy->checkObjectCollision(*m_player)) {
                    endgame();
                }
                else if (enemy->getY() + enemy->getHeight() >= m_line_y) {
                    endgame();
                }
                else if (enemy->checkMapCollision(m_board_width, m_line_y)) {
                    on_edge = true;
                }
                else if (shooting_unit == i) {
                    m_enemy_bullets.push_back(enemy->shoot());
                }
            }
        }
    }
    if (on_edge) {
        for (auto enemy : m_enemies) {
            if (!enemy->is_dead() && !enemy->is_dying()) {
                enemy->setSpeed(-1 * enemy->getDx(), 25);
                enemy->move();
                enemy->setSpeed(enemy->getDx(), 0);
            }
        }
    }
}

void Game::updateEnemyBullets() {
    for (int i = 0; i < static_cast<int>(m_enemy_bullets.size()); i++) {
        shared_ptr<Bullet> bullet = m_enemy_bullets[static_cast<size_t>(i)];
        if (!m_player->is_dying()) {
            bullet->move();
        }
        //board_height - 60 = y of green line
        if (bullet->checkMapCollision(m_board_width, m_board_height - 60)) {
            m_enemy_bullets.erase(m_enemy_bullets.begin() + i);
            i--;
            continue;
        }
        if (bullet->checkObjectCollision(*m_player)) {
            m_enemy_bullets.erase(m_enemy_bullets.begin() + i);
            i--;
            m_sound_manager->playerKill();
            m_player->kill();
            continue;
        }
        for (auto texture : m_textures) {
            if (texture->checkHit(bullet)) {
                m_enemy_bullets.erase(m_enemy_bullets.begin() + i);
                i--;
                continue;
            }
        }
        m_toDraw.push_back(bullet);
    }
}

void Game::updateUfo() {
    if (m_ufo) {
        if (m_ufo->is_dead()) {
            m_score += m_ufo->getPoints();
            m_ufo = nullptr;
            return;
        }
        if (m_ufo->checkMapCollision(m_board_width, m_board_height)) {
            m_ufo = nullptr;
            return;
        }
        if (!m_ufo->is_dying()) {
            m_toDraw.push_back(m_ufo);
        }
        m_toUpdate.push_back(m_ufo);

        if (!m_ufo->is_dying()){
            m_ufo->move();
        }
    }
    else if (!m_ufo) {
        if (rand() % 2000 == 0) {
            m_ufo = shared_ptr<Ufo>(new Ufo(550, 60, -m_speed / 2));
            m_sound_manager->ufoCreating();
        }
        else if (rand() % 2000 == 1) {
            m_ufo = shared_ptr<Ufo>(new Ufo(1, 60, m_speed / 2));
            m_sound_manager->ufoCreating();
        }
    }
}

void Game::checkDifficult() {
    size_t max_enemies = 13 * 5;
    if (m_enemies.size() == 0) {
        m_difficult = 0;
    }
    else if (m_enemies.size() > max_enemies / 2) {
        m_difficult = 1;
    }
    else if (m_enemies.size() > max_enemies / 6 && m_enemies.size() < max_enemies / 2) {
        m_difficult = 2;
    }
    else if (m_enemies.size() > 0 && m_enemies.size() < max_enemies / 6) {
        m_difficult = 3;
    }
}

void Game::draw(QPainter& painter) {
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, m_board_width, m_board_height);
    painter.setBrush(Qt::green);
    painter.drawRect(0, m_line_y, 600, 2);
    for (int i = 0; i < m_lives; i++) {
        painter.drawPixmap(30 + i * 50, 560, m_player->getDefaultPicture());
    }
    if (m_ufo) {
        if (m_ufo->is_dying()) {
            printNumber(m_ufo->getPoints(), m_ufo->getX(), m_ufo->getY(), painter);
        }
    }
    printScore(painter);
    printTitle(painter);
    for (auto drawable : m_toDraw) {
        drawable->draw(painter);
    }
}


void Game::printNumber(int value, int start_x, int start_y, QPainter& painter) {
    vector<shared_ptr<QPixmap>> images;
    QPixmap image;
    QPixmap sprite_sheet = QPixmap(":/sources/images/sprite_sheet.png");
    for (int i = 0; i < 10; i++) {
        image = sprite_sheet.copy(156 + i * 20, 266, 10, 14);
        images.push_back(shared_ptr<QPixmap>(new QPixmap(image)));
    }

    vector<int> digits;
    if (value == 0) {
        digits.push_back(0);
    }
    else {
        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        painter.drawPixmap(start_x, start_y, *images[static_cast<size_t>(digits[static_cast<size_t>(i)])]);
        start_x += 15;
    }
}

void Game::readHighScore() {
    vector<pair<string, int>> records;
    records = Record_File::getRecords(m_source_path + "high_scores.txt");
    if (records.size() > 0) {
        m_highscore = records[0].second;
    }
    else {
        m_highscore = 0;
    }
}

void Game::printTitle(QPainter& painter) {
    QPixmap title(":/sources/images/title.png");
    painter.drawPixmap(210, 5, title);
}

void Game::printScore(QPainter& painter) {
    int score_x = 20;
    int score_y = 10;
    QPixmap sprite_sheet = QPixmap(":/sources/images/sprite_sheet.png");
    QPixmap score_text = sprite_sheet.copy(56, 264, 74, 14);
    painter.drawPixmap(score_x, score_y, score_text);
    score_x += 10;
    score_y += 25;
    printNumber(m_score, score_x, score_y, painter);
    QPixmap high_score_text = sprite_sheet.copy(8, 264, 122, 14);
    score_x = 450;
    score_y = 10;
    painter.drawPixmap(score_x, score_y, high_score_text);
    score_x += 20;
    score_y += 25;
    printNumber(m_highscore, score_x, score_y, painter);
}

void Game::endgame() {
    m_endgame = true;
    m_enemy_bullets.clear();
    m_player_bullet = nullptr;
}

bool Game::is_endgame() {
    return this->m_endgame;
}

void Game::mute() {
    m_sound_manager->stop();
}

void Game::unmute() {
    m_sound_manager->play();
}

bool Game::is_muted() {
    return !m_sound_manager->is_playing();
}

Game::~Game() {

}
