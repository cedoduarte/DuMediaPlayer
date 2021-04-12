#include "ui_DuMediaPlayerPreferencesDialog.h"
#include "DuMediaPlayerPreferencesDialog.h"
#include "DuMediaPlayerSettings.h"
#include <QMessageBox>

namespace DuarteCorporation
{
DuMediaPlayerPreferencesDialog::DuMediaPlayerPreferencesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DuMediaPlayerPreferencesDialog)
{
    ui->setupUi(this);
    int lang = DuMediaPlayerSettings::load(DuMediaPlayerSettings::G_SETTINGS,
                                           DuMediaPlayerSettings::K_LANGUAJE,
                                           0).toInt();
    int style = DuMediaPlayerSettings::load(DuMediaPlayerSettings::G_SETTINGS,
                                            DuMediaPlayerSettings::K_STYLE,
                                            0).toInt();
    ui->langListWidget->setCurrentRow(lang);
    ui->styleListWidget->setCurrentRow(style);
    ui->page_1->layout()->setMargin(0);
    ui->page_2->layout()->setMargin(0);
}

DuMediaPlayerPreferencesDialog::~DuMediaPlayerPreferencesDialog()
{
    delete ui;
}

void DuMediaPlayerPreferencesDialog::on_listWidget_clicked(
        const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(index.row());
}

void DuMediaPlayerPreferencesDialog::on_accept_clicked()
{
    QMessageBox::warning(this, tr("Advertencia"),
         tr("Algunos ajustes requieren reiniciar la aplicación"));
    DuMediaPlayerSettings::save(DuMediaPlayerSettings::G_SETTINGS,
                                DuMediaPlayerSettings::K_LANGUAJE,
                                ui->langListWidget->currentRow());
    DuMediaPlayerSettings::save(DuMediaPlayerSettings::G_SETTINGS,
                                DuMediaPlayerSettings::K_STYLE,
                                ui->styleListWidget->currentRow());
    accept();
}
} // end namespace DuarteCorporation

