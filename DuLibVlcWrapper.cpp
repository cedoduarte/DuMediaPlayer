#include "DuLibVlcWrapper.h"
#include <vlc/vlc.h>
#include <QWidget>
#include <QTimer>
#include <QUrl>

namespace DuarteCorporation
{
DuLibVlcWrapper::DuLibVlcWrapper(QObject *parent)
    : QObject(parent)
{
    mMedia = nullptr;
    mTimer = new QTimer(this);
    mInstance = libvlc_new(0, nullptr);
    mMediaPlayer = libvlc_media_player_new(mInstance);

    connect(mTimer, &QTimer::timeout, [&]() {
        emit positionChanged(position());
        emit mediaStatusChanged(status());
        if (status() == END_OF_MEDIA) {
            mTimer->stop();
        }
    });
}

DuLibVlcWrapper::~DuLibVlcWrapper()
{
    libvlc_media_release(mMedia);
    libvlc_media_player_release(mMediaPlayer);
    libvlc_release(mInstance);
}

void DuLibVlcWrapper::setVideoOutput(QWidget *videoWidget)
{
    mVideoWidget = videoWidget;
    libvlc_media_player_set_hwnd(mMediaPlayer, reinterpret_cast<HWND *>
                                 (mVideoWidget->winId()));
}

void DuLibVlcWrapper::setMedia(const QUrl &url)
{
    libvlc_media_release(mMedia);
    mMedia = libvlc_media_new_location(mInstance,
                url.url().toStdString().c_str());
    libvlc_media_player_set_media(mMediaPlayer, mMedia);
    libvlc_media_parse(mMedia);
    emit durationChanged(duration());
    mTimer->start(1);
}

void DuLibVlcWrapper::setPosition(float pos)
{
    libvlc_media_player_set_position(mMediaPlayer, pos);
}

float DuLibVlcWrapper::position()
{
    return libvlc_media_player_get_position(mMediaPlayer);
}

void DuLibVlcWrapper::setVolume(int volume)
{
    libvlc_audio_set_volume(mMediaPlayer, volume);
}

void DuLibVlcWrapper::setMute(bool mute)
{
    libvlc_audio_set_mute(mMediaPlayer, mute);
}

int DuLibVlcWrapper::volume()
{
    return libvlc_audio_get_volume(mMediaPlayer);
}

bool DuLibVlcWrapper::isMute()
{
    return libvlc_audio_get_mute(mMediaPlayer);
}

void DuLibVlcWrapper::play()
{
    libvlc_media_player_play(mMediaPlayer);
    emit mediaStatusChanged(status());
    mTimer->start(1);
}

bool DuLibVlcWrapper::isPlaying()
{
    return libvlc_media_player_is_playing(mMediaPlayer);
}

void DuLibVlcWrapper::pause()
{
    libvlc_media_player_pause(mMediaPlayer);
    emit mediaStatusChanged(status());
}

void DuLibVlcWrapper::stop()
{
    mTimer->stop();
    libvlc_media_player_stop(mMediaPlayer);
    emit mediaStatusChanged(status());
}

int DuLibVlcWrapper::status()
{
    return libvlc_media_player_get_state(mMediaPlayer);
}

bool DuLibVlcWrapper::hasMedia()
{
    return libvlc_media_player_get_media(mMediaPlayer);
}

qint64 DuLibVlcWrapper::duration()
{
    return libvlc_media_get_duration(mMedia);
}

qint64 DuLibVlcWrapper::mediaLenght()
{
    return libvlc_media_player_get_length(mMediaPlayer);
}
} // end namespace DuarteCorporation
