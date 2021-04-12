#ifndef DUMEDIAPLAYERVIDEOWIDGET_H
#define DUMEDIAPLAYERVIDEOWIDGET_H

#include <QVideoWidget>

namespace DuarteCorporation
{
class DuMediaPlayerVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    DuMediaPlayerVideoWidget(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *e);
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERVIDEOWIDGET_H
