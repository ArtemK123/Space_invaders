#include "window.h"
#include "ui_window.h"
#include <QTimer>
#include <QPainter>
#include <vector>


Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    m_game = new Game();
    this->setFixedSize(m_game->m_board_width, m_game->m_board_height);
    ui->setupUi(this);
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    m_timer->start(30);

    m_game->start();
}

void Window::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    m_game->draw(painter);
}

void Window::timerTick() {
    if (!m_game->is_endgame()) {
        m_game->update();
        this->update();
    }

}

void Window::keyPressEvent(QKeyEvent* e) {
    switch (e->key())
    {
    case (Qt::Key_Left): {
        m_game->m_buttoms.left = true;
        break;
    }
    case (Qt::Key_Right): {
        m_game->m_buttoms.right = true;
        break;
    }
    case (Qt::Key_Space): {
        m_game->m_buttoms.space = true;
        break;
    }
    }
};

void Window::keyReleaseEvent(QKeyEvent* e) {
    switch (e->key())
    {
    case (Qt::Key_Left): {
        m_game->m_buttoms.left = false;
        break;
    }
    case (Qt::Key_Right): {
        m_game->m_buttoms.right = false;
        break;
    }
    case (Qt::Key_Space): {
        m_game->m_buttoms.space = false;
        break;
    }
    case (Qt::Key_T): {
        m_game->start();
        break;
    }
    case (Qt::Key_P): {
        m_game->pause();
        break;
    }
    }
}

Window::~Window()
{
    delete ui;
    delete m_game;
}
