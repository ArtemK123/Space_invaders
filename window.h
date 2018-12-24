#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <game.h>
#include <QKeyEvent>

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
    Ui::Window *ui;
    QTimer* m_timer;
    Game* m_game;
    shared_ptr<Pressed_Buttons> m_buttons;

    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;

private slots:
    void timerTick();

};


#endif // WIDGET_H
