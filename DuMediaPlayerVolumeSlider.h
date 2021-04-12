#ifndef DUMEDIAPLAYERVOLUMESLIDER_H
#define DUMEDIAPLAYERVOLUMESLIDER_H

#include <QWidget>

namespace Ui
{
class DuMediaPlayerVolumeSlider;
}

namespace DuarteCorporation
{
class DuMediaPlayerVolumeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit DuMediaPlayerVolumeSlider(QWidget *parent = nullptr);
    ~DuMediaPlayerVolumeSlider();
    void setValue(int value);
    int value() const;
    void setMuted(bool _muted);

    bool isMuted() const
    {
        return mMuted;
    }
signals:
    void muted(bool);
    int valueChanged(int);
private slots:
    void on_mute_clicked();
private:
    Ui::DuMediaPlayerVolumeSlider *ui;
    bool mMuted;
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERVOLUMESLIDER_H
