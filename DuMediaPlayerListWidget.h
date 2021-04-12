#ifndef DUMEDIAPLAYERLISTWIDGET_H
#define DUMEDIAPLAYERLISTWIDGET_H

#include <QListWidget>

class QAction;

namespace DuarteCorporation
{
class DuMediaPlayerListWidget : public QListWidget
{
public:
    DuMediaPlayerListWidget(QWidget *parent = nullptr);
private:
    QAction *mDelete;
    QAction *mDown;
    QAction *mUp;
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERLISTWIDGET_H
