#include "sound.h"
#include <iostream>

Sound_Manager::Sound_Manager(QObject* parent, string sound_directory) {
    m_frame_count = 0;
    m_playing = false;
    m_source_path = sound_directory;

    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "fastinvader4.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "fastinvader3.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "fastinvader2.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "fastinvader1.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "shoot.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "invaderkilled.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "ufo_lowpitch.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "ufo_highpitch.wav").c_str()))));
    m_media.push_back(shared_ptr<QMediaContent>(new QMediaContent(QUrl::fromLocalFile((m_source_path + "explosion.wav").c_str()))));

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



