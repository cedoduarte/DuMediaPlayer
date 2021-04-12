#include "ui_DuMediaPlayerVolumeSlider.h"
#include "DuMediaPlayerVolumeSlider.h"

namespace DuarteCorporation
{
DuMediaPlayerVolumeSlider::DuMediaPlayerVolumeSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DuMediaPlayerVolumeSlider)
{
    ui->setupUi(this);
    mMuted = false;
    layout()->setMargin(0);

    connect(ui->horizontalSlider, &QSlider::valueChanged, [&](int value) {
        emit valueChanged(value);
    });
}

DuMediaPlayerVolumeSlider::~DuMediaPlayerVolumeSlider()
{
    delete ui;
}

void DuMediaPlayerVolumeSlider::setValue(int value)
{
    ui->horizontalSlider->setValue(value);
}

int DuMediaPlayerVolumeSlider::value() const
{
    return ui->horizontalSlider->value();
}

void DuMediaPlayerVolumeSlider::setMuted(bool _muted)
{
    if (_muted) {
        mMuted = true;
        ui->mute->setIcon(QIcon(":muted"));
    } else {
        mMuted = false;
        ui->mute->setIcon(QIcon(":sounded"));
    }
    emit muted(mMuted);
}

void DuMediaPlayerVolumeSlider::on_mute_clicked()
{
    if (mMuted) {
        mMuted = false;
        ui->mute->setIcon(QIcon(":sounded"));
    } else {
        mMuted = true;
        ui->mute->setIcon(QIcon(":muted"));
    }
    emit muted(mMuted);
}
} // end namespace DuarteCorporation
