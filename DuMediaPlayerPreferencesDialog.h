#ifndef DUMEDIAPLAYERPREFERENCESDIALOG_H
#define DUMEDIAPLAYERPREFERENCESDIALOG_H

#include <QDialog>

namespace Ui
{
class DuMediaPlayerPreferencesDialog;
}

namespace DuarteCorporation
{
class DuMediaPlayerPreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    enum Languaje
    {
        SPANISH,
        ENGLISH,
        PORTUGUESE,
        RUSSIAN,
        CHINESE,
        FRENCH,
        ITALIAN,
        GERMAN,
        JAPANESE
    };

    enum Style
    {
        WINDOWS_VISTA,
        FUSION,
    };

    explicit DuMediaPlayerPreferencesDialog(QWidget *parent = nullptr);
    ~DuMediaPlayerPreferencesDialog();
private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_accept_clicked();
private:
    Ui::DuMediaPlayerPreferencesDialog *ui;
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERPREFERENCESDIALOG_H
