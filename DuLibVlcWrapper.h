#ifndef DUVLCWRAPPER_H
#define DUVLCWRAPPER_H

#include <QObject>

class QTimer;

using DuVlcMedia = struct libvlc_media_t;
using DuVlcInstance = struct libvlc_instance_t;
using DuVlcMediaPlayer = struct libvlc_media_player_t;

namespace DuarteCorporation
{
class DuLibVlcWrapper : public QObject
{
    Q_OBJECT
public:
    enum Status
    {
        NONE,
        OPENING,
        BUFFERING,
        PLAYING,
        PAUSED,
        STOPPED,
        END_OF_MEDIA,
        ERROR
    };

    DuLibVlcWrapper(QObject *parent = nullptr);
    ~DuLibVlcWrapper();
    void setVideoOutput(QWidget *videoWidget);
    void setMedia(const QUrl &url);
    qint64 mediaLenght();
    qint64 duration();
    float position();
    bool isPlaying();
    bool hasMedia();
    bool isMute();
    int volume();
    int status();
public slots:
    void setPosition(float pos);
    void setVolume(int volume);
    void setMute(bool mute);
    void play();
    void pause();
    void stop();
signals:
    void positionChanged(float);
    void mediaStatusChanged(int);
    void durationChanged(qint64);
private:
    QTimer *mTimer;
    DuVlcMedia *mMedia;
    QWidget *mVideoWidget;
    DuVlcInstance *mInstance;
    DuVlcMediaPlayer *mMediaPlayer;
};
} // end namespace DuarteCorporation

#endif // DUVLCWRAPPER_H
