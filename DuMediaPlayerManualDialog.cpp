#include "ui_DuMediaPlayerManualDialog.h"
#include "DuMediaPlayerManualDialog.h"

namespace DuarteCorporation
{
DuMediaPlayerManualDialog::DuMediaPlayerManualDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DuMediaPlayerManualDialog)
{
    ui->setupUi(this);
    layout()->setMargin(0);
}

DuMediaPlayerManualDialog::~DuMediaPlayerManualDialog()
{
    delete ui;
}
} // end namespace DuarteCorporation
