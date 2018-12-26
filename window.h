#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "game.h"
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "ui_menu.h"
#include "ui_game.h"
#include "ui_records.h"
#include "ui_new_record.h"


namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;

private:
    enum State {MENU, GAME, NEW_RECORD, RECORDS_TABLE};
    State m_state;
    Ui::Window *ui;
    shared_ptr<Ui_Menu> m_ui_menu;
    shared_ptr<Ui_Game> m_ui_game;
    shared_ptr<Ui_Records> m_ui_records;
    shared_ptr<Ui_NewRecord> m_ui_new_record;


    unique_ptr<QTimer> m_timer;
    unique_ptr<Game> m_game;
    shared_ptr<Pressed_Buttons> m_buttons;

    void showMenu();
    void showGame();
    void showNewRecord();
    void showRecordsTable();

    void hideAll();

    void addRecord(pair<string, int> record);
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void setState(State state);


private slots:
    void timerTick();
    void menu_start_button_pressed();
    void menu_records_button_pressed();
    void new_record_button_pressed();
    void records_table_menu_button_pressed();
};


#endif // WIDGET_H
