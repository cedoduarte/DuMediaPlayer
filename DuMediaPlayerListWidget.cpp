#include "DuMediaPlayerListWidget.h"
#include <QAction>

namespace DuarteCorporation
{
DuMediaPlayerListWidget::DuMediaPlayerListWidget(QWidget *parent)
    : QListWidget(parent)
{
    mDelete = new QAction(QIcon(":delete"), tr("Eliminar"), this);
    mUp = new QAction(QIcon(":up"), tr("Subir"), this);
    mDown = new QAction(QIcon(":down"), tr("Bajar"), this);
    addActions({mDelete, mUp, mDown});

    // deletes current selected item
    connect(mDelete, &QAction::triggered, [&]() {
        delete currentItem();
    });

    // sets up the current selected item
    connect(mUp, &QAction::triggered, [&]() {
        int row = currentRow();
        insertItem(row-1, takeItem(row));
    });

    // sets down the current selected item
    connect(mDown, &QAction::triggered, [&]() {
        int row = currentRow();
        insertItem(row+1, takeItem(row));
    });
}
} // end namespace DuarteCorporation
