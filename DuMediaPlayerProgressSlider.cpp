#include "DuMediaPlayerProgressSlider.h"

namespace DuarteCorporation
{
DuMediaPlayerProgressSlider::DuMediaPlayerProgressSlider(QWidget *parent)
    : QSlider(Qt::Horizontal, parent)
{
}

void DuMediaPlayerProgressSlider::mousePressEvent(QMouseEvent *e)
{
    emit stop();
    QSlider::mousePressEvent(e);
}

void DuMediaPlayerProgressSlider::mouseReleaseEvent(QMouseEvent *e)
{
    emit play(value());
    QSlider::mouseReleaseEvent(e);
}
} // end namespace DuarteCorporation
