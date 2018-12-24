#include "sound.h"

Sound_Manager::Sound_Manager() {
    m_frame_count = 0;
    m_sounds = vector<shared_ptr<QSound>>();
    m_playing = false;

    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "fastinvader1.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "fastinvader2.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "fastinvader3.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "fastinvader4.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "shoot.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "invaderkilled.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "ufo_lowpitch.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "ufo_highpitch.wav").c_str())));
    m_sounds.push_back(shared_ptr<QSound>(new QSound((source_path + "explosion.wav").c_str())));
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
            m_sounds[0]->play();
            m_frame_count++;
            break;
        }
        case 1: {
            m_sounds[1]->play();
            m_frame_count++;
            break;
        }
        case 2: {
            m_sounds[2]->play();
            m_frame_count++;
            break;
        }
        case 3: {
            m_sounds[3]->play();
            m_frame_count = 0;
            break;
        }
        }
    }
}
void Sound_Manager::shoot() {
    if (m_playing) {
        m_sounds[4]->play();
    }
}

void Sound_Manager::enemyKill() {
    if (m_playing) {
        m_sounds[5]->play();
    }
}
void Sound_Manager::ufoCreating() {
    if (m_playing) {
        m_sounds[6]->play();
    }
}

void Sound_Manager::ufoKill() {
    if (m_playing) {
        m_sounds[7]->play();
    }
}

void Sound_Manager::playerKill() {
    if (m_playing) {
        m_sounds[8]->play();
    }
}

Sound_Manager::~Sound_Manager() {
}
