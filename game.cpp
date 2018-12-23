#include "game.h"

Game::Game()
{
    m_frame_count = 0;
    m_speed = 5;
    m_lives = 3;
    m_score = 0;
    m_endgame = false;

    m_player = shared_ptr<Player>(new Player(285, 500, m_speed));
    m_player_bullet = nullptr;
    m_ufo = nullptr;
}

void Game::start() {
    cout<<"start"<<endl;
    m_enemies.clear();
    m_textures.clear();
    m_enemy_bullets.clear();
    create_enemies();
    create_textures();
    m_frame_count = 0;
    m_score = 0;
    m_endgame = false;
    m_lives = 3;
    m_player->setX(285);
    m_is_pause = false;
}

void Game::pause() {
    m_is_pause = (m_is_pause) ? false : true;
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


void Game::draw(QPainter& painter) {
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, 20 * 30, 20 * 30);
    for (auto texture : m_textures) {
        texture->draw(painter);
    }
    for (auto unit : m_enemies) {
        unit->draw(painter);
    }
    for (auto bullet : m_enemy_bullets) {
        bullet->draw(painter);
    }
    if (m_player_bullet) {
        m_player_bullet->draw(painter);
    }
    painter.setBrush(Qt::green);
    painter.drawRect(0, 540, 600, 2);
    for (int i = 0; i < m_lives; i++) {
        painter.drawPixmap(30 + i * 50, 560, m_player->getDefaultPicture());
    }
    if (m_ufo) {
        m_ufo->draw(painter);
    }
    printScore(painter);
    m_player->draw(painter);
}

void Game::printScore(QPainter& painter) {
    vector<shared_ptr<QPixmap>> images;
    int start_x = 20;
    int start_y = 10;
    QPixmap image;
    QPixmap sprite_sheet = QPixmap(":/sources/sprite_sheet.png");
    QPixmap score_text = sprite_sheet.copy(56, 264, 74, 14);
    painter.drawPixmap(start_x, start_y, score_text);
    start_x += 10;
    start_y += 25;
    for (int i = 0; i < 10; i++) {
        image = sprite_sheet.copy(156 + i * 20, 266, 10, 14);
        images.push_back(shared_ptr<QPixmap>(new QPixmap(image)));
    }

    vector<int> digits;
    int score = m_score;
    while (score > 0) {
        digits.push_back(score % 10);
        score /= 10;
    }

    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        painter.drawPixmap(start_x, start_y, *images[static_cast<size_t>(digits[static_cast<size_t>(i)])]);
        start_x += 15;
    }
}

void Game::updatePlayer() {
    if (!m_buttoms.left && m_buttoms.right) {
        m_player->setSpeed(m_speed, 0);
        m_player->move();
    }
    if (m_buttoms.left && !m_buttoms.right) {
        m_player->setSpeed(-m_speed, 0);
        m_player->move();
    }
    if (m_buttoms.space && m_player_bullet == nullptr) {
        m_player_bullet = m_player->shoot();
    }
    if (m_player->checkMapCollision(m_board_width, m_board_height)) {
        m_player->moveBack();
    }
}

void Game::updatePlayerBullet() {
    if (m_player_bullet != nullptr) {
        m_player_bullet->move();
        if (m_player_bullet->checkMapCollision(m_board_width, m_board_height)) {
            m_player_bullet = nullptr;
            return;
        }
        for (int i = 0; i < static_cast<int>(m_enemies.size()); i++) {
            shared_ptr<Enemy> enemy = m_enemies[static_cast<size_t>(i)];
            if (m_player_bullet && m_player_bullet->checkObjectCollision(*enemy)) {
                enemy->kill();
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
            m_player_bullet = nullptr;
        }
    }
}

void Game::updateEnemies() {
    bool on_edge = false;
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
        else if (m_frame_count == 10) {
            if (rand() % (m_speed * 30) == 0) {
                m_enemy_bullets.push_back(enemy->shoot());
            }
            enemy->animate();
            enemy->move();
            if (enemy->checkMapCollision(m_board_width, m_board_height)) {
                on_edge = true;
            }
        }
    }
    if (on_edge) {
        for (auto enemy : m_enemies) {
            enemy->setSpeed(-1 * enemy->getDx(), 2 * m_speed);
            enemy->move();
            enemy->setSpeed(enemy->getDx(), 0);
        }
    }

    if (m_ufo) {
        if (m_ufo->is_dead()) {
            m_score += m_ufo->getPoints();
            m_ufo = nullptr;
        }
        else if (m_ufo->checkMapCollision(m_board_width, m_board_height)) {
            m_ufo = nullptr;
        }
        else if (m_frame_count % 2 == 0) {
            m_ufo->move();
        }
    }
    else if (!m_ufo) {
        if (rand() % 3000 == 0) {
            m_ufo = shared_ptr<Ufo>(new Ufo(550, 60, -m_speed));
        }
        else if (rand() % 3000 == 1) {
            m_ufo = shared_ptr<Ufo>(new Ufo(0, 60, m_speed));
        }
    }
}

void Game::updateEnemyBullets() {
    for (int i = 0; i < static_cast<int>(m_enemy_bullets.size()); i++) {
        shared_ptr<Bullet> bullet = m_enemy_bullets[static_cast<size_t>(i)];
        bullet->move();
        //board_height - 60 = y of green line
        if (bullet->checkMapCollision(m_board_width, m_board_height - 60)) {
            m_enemy_bullets.erase(m_enemy_bullets.begin() + i);
            i--;
            continue;
        }
        if (bullet->checkObjectCollision(*m_player)) {
            m_enemy_bullets.erase(m_enemy_bullets.begin() + i);
            i--;
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
    }
}

void Game::update() {
    if (!m_is_pause && !m_player->is_dying()) {
        updatePlayer();
        updatePlayerBullet();

        updateEnemies();
        updateEnemyBullets();

        if (m_enemies.size() == 0) {
            create_enemies();
            m_lives++;
        }
        m_frame_count = (m_frame_count == 10) ? 0 : m_frame_count + 1;
    }
    else if (m_player->is_dead()) {
        m_lives--;
        if (m_lives == 0) {
            m_endgame = true;
        }
        else {
            m_player->relive();
        }
    }
}

bool Game::is_endgame() {
    return this->m_endgame;
}

Game::~Game() {

}
