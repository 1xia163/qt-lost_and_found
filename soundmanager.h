#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    static SoundManager& instance();

    void playClick();        // 播放点击音效
    void startBGM();         // 开始背景音乐
    void stopBGM();          // 停止背景音乐

private:
    SoundManager();
    ~SoundManager();

    QSoundEffect *clickSound;
    QMediaPlayer *bgmPlayer;
    QAudioOutput *audioOutput;
};

#endif // SOUNDMANAGER_H