#include "DuMediaPlayerVideoWidget.h"
#include "DuMediaPlayerMainWindow.h"
#include "DuLibVlcWrapper.h"
#include <QCloseEvent>
#include <QKeyEvent>
#include <QAction>

namespace DuarteCorporation
{
DuMediaPlayerVideoWidget::DuMediaPlayerVideoWidget(QWidget *parent)
    : QVideoWidget(parent)
{
}

void DuMediaPlayerVideoWidget::keyPressEvent(QKeyEvent *e)
{
    int k = e->key();
    auto _parent = static_cast<DuMediaPlayerMainWindow *>(parent());
    if (k == Qt::Key_Escape) {
        setFullScreen(false);
        _parent->setCentralWidget(this);
    } else if (k == Qt::Key_Space) {
        if (_parent->mediaPlayer()->status()
                == DuLibVlcWrapper::PLAYING) {
            _parent->mediaPlayer()->pause();
        } else {
            _parent->mediaPlayer()->play();
        }
    }
}
} // end namespace DuarteCorporation
