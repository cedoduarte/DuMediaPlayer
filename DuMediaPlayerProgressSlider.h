#ifndef DUMEDIAPLAYERPROGRESSSLIDER_H
#define DUMEDIAPLAYERPROGRESSSLIDER_H

#include <QSlider>

namespace DuarteCorporation
{
class DuMediaPlayerProgressSlider : public QSlider
{
    Q_OBJECT
public:
    DuMediaPlayerProgressSlider(QWidget *parent = nullptr);
signals:
    void stop();
    void play(int);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERPROGRESSSLIDER_H
