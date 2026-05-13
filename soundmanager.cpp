#include "soundmanager.h"

SoundManager& SoundManager::instance()
{
    static SoundManager manager;
    return manager;
}

SoundManager::SoundManager()
{
    // 点击音效（用 QSoundEffect，适合短音效）
    clickSound = new QSoundEffect(this);
    clickSound->setSource(QUrl("qrc:/sound_effects/click.wav"));
    clickSound->setVolume(1);

    // 背景音乐（用 QMediaPlayer，适合长音频）
    bgmPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    bgmPlayer->setAudioOutput(audioOutput);
    bgmPlayer->setSource(QUrl("qrc:/effects/bgm.wav"));
    audioOutput->setVolume(0.05);  // 背景音乐音量 30%
}

SoundManager::~SoundManager()
{
    bgmPlayer->stop();
}

void SoundManager::playClick()
{
    if (clickSound->isPlaying()) {
        clickSound->stop();  // 如果正在播放，先停止再重新播放（让快速连点也能听到音效）
    }
    clickSound->play();
}

void SoundManager::startBGM()
{
    bgmPlayer->setLoops(QMediaPlayer::Infinite);  // 无限循环
    bgmPlayer->play();
}

void SoundManager::stopBGM()
{
    bgmPlayer->stop();
}