#ifndef SOUND_H
#define SOUND_H

#include <QSound>
#include <memory>
#include <QMediaPlayer>
#include <QMediaPlaylist>

using namespace std;

class Sound_Manager {
protected:

    vector<shared_ptr<QMediaPlayer>> m_tracks;
    vector<shared_ptr<QMediaContent>> m_media;

    int m_frame_count;
    const string source_path = "./../Space_invaders/sources/sounds/";
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

    Sound_Manager(QObject* parent);
    ~Sound_Manager();
};

#endif // SOUND_H
