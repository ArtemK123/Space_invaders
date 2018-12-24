#ifndef SOUND_H
#define SOUND_H

#include <QSound>
#include <memory>
#include <QMediaPlayer>
#include <QMediaPlaylist>

using namespace std;

class Sound_Manager {
protected:
    int m_frame_count;
    const string source_path = "./../Space_invaders/sources/sounds/";
    vector<shared_ptr<QSound>> m_sounds;
    bool m_playing;

public:
    void background();
    void shoot();
    void enemyKill();
    void ufoCreating();
    void ufoKill();
    void playerKill();
    void play();
    void stop();
    bool is_playing();

    Sound_Manager();
    ~Sound_Manager();
};










/*class Sound_Manager {
protected:
    int m_frame_count;
    string source_path = "./../Space_invaders/sources/sounds/";

public:
    void background();
    void shoot();
    void enemyKill();
    void ufoCreating();
    void ufoKill();
    void playerKill();

    Sound_Manager();
    ~Sound_Manager();
};*/

#endif // SOUND_H
