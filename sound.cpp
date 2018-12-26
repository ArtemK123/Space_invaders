#include "sound.h"
#include <iostream>

Sound_Manager::Sound_Manager(QObject* parent) {
    m_frame_count = 0;
    m_playing = false;
//    m_track1 = shared_ptr<QMediaPlayer>(new QMediaPlayer(parent));
//    m_track2 = shared_ptr<QMediaPlayer>(new QMediaPlayer(parent));
//    m_track3 = shared_ptr<QMediaPlayer>(new QMediaPlayer(parent));
//    m_track4 = shared_ptr<QMediaPlayer>(new QMediaPlayer(parent));

//    m_playlist = shared_ptr<QMediaPlaylist>(new QMediaPlaylist());
//    m_track1->setPlaylist(m_playlist.get());
//    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);



//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/fastinvader1.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/fastinvader2.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/fastinvader3.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/fastinvader4.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/shoot.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/invaderkilled.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/ufo_lowpitch.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/ugo_highpitch.wav"))));
//    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile(":/sources/sounds/explosion.wav"))));


    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "fastinvader4.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "fastinvader3.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "fastinvader2.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "fastinvader1.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "shoot.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "invaderkilled.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "ufo_lowpitch.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "ufo_highpitch.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((source_path + "explosion.wav").c_str()))));

    for (auto record : m_media) {
        shared_ptr<QMediaPlayer> track = shared_ptr<QMediaPlayer>(new QMediaPlayer(parent));
        track->setMedia(*record);
        track->stop();
        m_tracks.push_back(track);
    }
    m_tracks[0]->setVolume(30);
    m_tracks[1]->setVolume(30);
    m_tracks[2]->setVolume(30);
    m_tracks[3]->setVolume(30);
}

void Sound_Manager::play() {
    m_playing = true;
}

void Sound_Manager::stop() {
    m_playing = false;
}


bool Sound_Manager::is_playing() {
    return m_playing;
}

void Sound_Manager::background() {
    if (m_playing) {
        switch (m_frame_count) {
        case 0: {
            m_tracks[0]->play();
            m_frame_count++;
            break;
        }
        case 1: {
            m_tracks[1]->play();
            m_frame_count++;
            break;
        }
        case 2: {
            m_tracks[2]->play();
            m_frame_count++;
            break;
        }
        case 3: {
            m_tracks[3]->play();
            m_frame_count = 0;
            break;
        }
        }

    }
}

void Sound_Manager::shoot() {
    if (m_playing) {
        m_tracks[4]->play();
    }
}

void Sound_Manager::enemyKill() {
    if (m_playing) {
        m_tracks[5]->play();
    }
}

void Sound_Manager::ufoCreating() {
    if (m_playing) {
        m_tracks[6]->play();
    }
}

void Sound_Manager::ufoKill() {
    if (m_playing) {
        m_tracks[7]->play();
    }
}

void Sound_Manager::playerKill() {
    if (m_playing) {
        m_tracks[8]->play();
    }
}

Sound_Manager::~Sound_Manager() {
}



