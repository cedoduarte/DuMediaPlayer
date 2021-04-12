#ifndef DUMEDIAPLAYERMANUALDIALOG_H
#define DUMEDIAPLAYERMANUALDIALOG_H

#include <QDialog>

namespace Ui
{
class DuMediaPlayerManualDialog;
}

namespace DuarteCorporation
{
class DuMediaPlayerManualDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DuMediaPlayerManualDialog(QWidget *parent = nullptr);
    ~DuMediaPlayerManualDialog();
private:
    Ui::DuMediaPlayerManualDialog *ui;
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERMANUALDIALOG_H
