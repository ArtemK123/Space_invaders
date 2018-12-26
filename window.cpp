#include "window.h"
#include "ui_window.h"
#include <QTimer>
#include <QPainter>
#include <vector>
#include <fstream>
#include <iostream>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    m_buttons = shared_ptr<Pressed_Buttons>(new Pressed_Buttons());
    m_game = unique_ptr<Game>(new Game(m_buttons, this));

    this->setFixedSize(m_game->m_board_width, m_game->m_board_height);

    m_ui_menu = shared_ptr<Ui_Menu>(new Ui_Menu());
    m_ui_game = shared_ptr<Ui_Game>(new Ui_Game());
    m_ui_records = shared_ptr<Ui_Records>(new Ui_Records());
    m_ui_new_record = shared_ptr<Ui_NewRecord>(new Ui_NewRecord());

    m_ui_menu->setupUi(this);
    m_ui_game->setupUi(this);
    m_ui_records->setupUi(this);
    m_ui_new_record->setupUi(this);
    ui->setupUi(this);

    connect(m_ui_menu->startButton, SIGNAL (clicked()), this, SLOT (menu_start_button_pressed()));
    connect(m_ui_menu->recordsButton, SIGNAL (clicked()), this, SLOT (menu_records_button_pressed()));
    connect(m_ui_records->menuButton, SIGNAL (clicked()), this, SLOT (records_table_menu_button_pressed()));
    connect(m_ui_new_record->enterButton, SIGNAL (clicked()), this, SLOT (new_record_button_pressed()));


    m_timer = unique_ptr<QTimer>(new QTimer());
    connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(timerTick()));
    m_timer->setInterval(30);

    setState(State::MENU);
}

void Window::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    if (m_state == State::GAME) {
        m_game->draw(painter);
    }
}

void Window::timerTick() {
    if (m_state == State::GAME && !m_game->is_endgame()) {
        m_game->update();
        this->update();
    }
    else if (m_state == State::GAME && m_game->is_endgame()) {
        setState(State::NEW_RECORD);
    }
}

void Window::keyPressEvent(QKeyEvent* e) {
    if (m_state == State::GAME) {
        switch (e->key())
        {
        case (Qt::Key_Left): {
            m_buttons->left = true;
            break;
        }
        case (Qt::Key_Right): {
            m_buttons->right = true;
            break;
        }
        case (Qt::Key_Space): {
            m_buttons->space = true;
            break;
        }
        }
    }
};

void Window::keyReleaseEvent(QKeyEvent* e) {
    if (m_state == State::GAME) {
        switch (e->key())
        {
        case (Qt::Key_Left): {
            m_buttons->left = false;
            break;
        }
        case (Qt::Key_Right): {
            m_buttons->right = false;
            break;
        }
        case (Qt::Key_Space): {
            m_buttons->space = false;
            break;
        }
        case (Qt::Key_R): {
            m_game->start();
            break;
        }
        case (Qt::Key_P): {
            m_game->pause();
            break;
        }
        case (Qt::Key_T): {
            m_game->endgame();
            break;
        }
        case (Qt::Key_M): {
            if (m_game->is_muted()) {
                m_game->unmute();
            }
            else {
                m_game->mute();
            }
            break;
        }
        }
    }
}

void Window::showMenu() {
    m_ui_menu->container->setEnabled(true);
    m_ui_menu->container->show();
}

void Window::showGame() {
    m_ui_game->container->setEnabled(true);
    m_ui_game->container->show();
}

void Window::showNewRecord() {
    m_ui_new_record->container->setEnabled(true);
    m_ui_new_record->container->show();
}

void Window::showRecordsTable() {
    m_ui_records->container->setEnabled(true);
    m_ui_records->container->show();
    vector<pair<string, int>> records = Record_file::getRecords();
    string text;
    m_ui_records->nameBox->clear();
    m_ui_records->scoreBox->clear();
    for (auto record : records) {
        m_ui_records->nameBox->append(QString(record.first.c_str()));
        m_ui_records->scoreBox->append(QString::number(record.second));
        m_ui_records->scoreBox->setAlignment(Qt::AlignRight);
    }
}

void Window::hideAll() {
    m_ui_menu->container->setEnabled(false);
    m_ui_menu->container->hide();
    m_ui_game->container->setEnabled(false);
    m_ui_game->container->hide();
    m_ui_records->container->setEnabled(false);
    m_ui_records->container->hide();
    m_ui_new_record->container->setEnabled(false);
    m_ui_new_record->container->hide();
}

void Window::menu_start_button_pressed() {
    setState(State::GAME);
}

void Window::menu_records_button_pressed() {
    setState(State::RECORDS_TABLE);
}

void Window::new_record_button_pressed() {
    pair<string, int> record;
    record.first = m_ui_new_record->nameBox->text().toStdString();
    record.second = m_ui_new_record->scoreBox->text().toInt();
    addRecord(record);
    setState(State::RECORDS_TABLE);
}

void Window::addRecord(pair<string, int> new_record) {
    vector<pair<string, int>> records = Record_file::getRecords();
    bool found = false;
    for (int i = 0; i < static_cast<int>(records.size()); i++) {
        if (new_record.second >= records[static_cast<size_t>(i)].second) {
            records.insert(records.begin() + i, new_record);
            found = true;
            break;
        }
    }
    if (!found) {
        records.push_back(new_record);
    }

    if (records.size() > 19) {
        records.erase(records.begin() + static_cast<int>((records.size() - 1)));
    }
    Record_file::writeRecords(records);
}



void Window::records_table_menu_button_pressed() {
    setState(State::MENU);
}

void Window::setState(State state) {
    m_state = state;
    switch (state) {
    case State::MENU : {
        hideAll();
        showMenu();
        m_timer->stop();
        break;
    }
    case State::GAME : {
        hideAll();
        //showGame();
        m_timer->start();
        m_game->start();
        break;
    }
    case State::NEW_RECORD : {
        showNewRecord();
        m_timer->stop();
        m_ui_new_record->scoreBox->setText(QString::number(m_game->getScore()));
        break;
    }
    case State::RECORDS_TABLE : {
        hideAll();
        showRecordsTable();
        m_timer->stop();
        break;
    }
    }
}

Window::~Window()
{
    delete ui;
}
