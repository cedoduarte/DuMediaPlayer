// DuarteCorporation include files
#include "DuMediaPlayerPreferencesDialog.h"
#include "DuMediaPlayerProgressSlider.h"
#include "ui_DuMediaPlayerMainWindow.h"
#include "DuMediaPlayerVolumeSlider.h"
#include "DuMediaPlayerManualDialog.h"
#include "DuMediaPlayerVideoWidget.h"
#include "DuMediaPlayerMainWindow.h"
#include "DuMediaPlayerSettings.h"
#include "DuLibVlcWrapper.h"

// Qt include files
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDropEvent>
#include <QFileInfo>
#include <QMimeData>
#include <QSlider>
#include <QLabel>
#include <QFile>

namespace DuarteCorporation
{
DuMediaPlayerMainWindow::DuMediaPlayerMainWindow(int argc, char **argv,
                                                 QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
    applySettings(argc, argv);
    connections();
}

DuMediaPlayerMainWindow::~DuMediaPlayerMainWindow()
{
    delete ui;
}

void DuMediaPlayerMainWindow::initialize()
{
    mMediaProgress = new DuMediaPlayerProgressSlider(this);
    mVideoWidget = new DuMediaPlayerVideoWidget(this);
    mVolSlider = new DuMediaPlayerVolumeSlider(this);
    mTimerLabel = new QLabel("00:00:00", this);
    mMediaPlayer = new DuLibVlcWrapper(this);
}

void DuMediaPlayerMainWindow::applySettings(int argc, char **argv)
{
    int vol = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_VOL,
             DuMediaPlayerSettings::K_VOL,
             100).toInt();
    bool muted = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_VOL,
             DuMediaPlayerSettings::K_MUTED,
             false).toBool();
    bool visible = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_VISIBLE,
             true).toBool();
    bool floating = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_FLOATING,
             false).toBool();
    auto geometry = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_MAINWINDOW,
             DuMediaPlayerSettings::K_MW_GEOMETRY,
             QRect(200, 200, 600, 400)).toRect();

    mVolSlider->setValue(vol);
    mVolSlider->setMuted(muted);
    mVolSlider->setMaximumWidth(150);
    ui->actionPlayList->setChecked(visible);
    mMediaPlayer->setVideoOutput(mVideoWidget);
    auto pgr = ui->mainToolBar->insertWidget(ui->actionRepetir, mMediaProgress);
    ui->mainToolBar->insertWidget(pgr, mVolSlider);
    ui->mainToolBar->insertSeparator(pgr);
    auto tm = ui->mainToolBar->insertWidget(ui->actionRepetir, mTimerLabel);
    ui->mainToolBar->insertSeparator(ui->actionRepetir);
    ui->mainToolBar->insertSeparator(tm);
    ui->dockWidgetContents->layout()->setMargin(0);
    ui->dockWidget->setWindowTitle(tr("Lista de reproducción"));
    ui->dockWidget->setVisible(ui->actionPlayList->isChecked());
    ui->dockWidget->setFloating(floating);

    if (floating) {
        auto gmty = DuMediaPlayerSettings::load
                (DuMediaPlayerSettings::G_PLAYLIST,
                 DuMediaPlayerSettings::K_GEOMETRY,
                 QRect(200, 200, 100, 200)).value<QRect>();
        ui->dockWidget->setGeometry(gmty);
    }
    for (int i = 1; i < argc; ++i) {
        ui->listWidget->addItem(new QListWidgetItem(QIcon(":mediafile"),
            argv[i]));
    }
    setAcceptDrops(true);
    setCentralWidget(mVideoWidget);
    setGeometry(geometry);
}

void DuMediaPlayerMainWindow::connections()
{
    connect(mMediaPlayer, &DuLibVlcWrapper::mediaStatusChanged,
            [&](int state) {
        if (state == DuLibVlcWrapper::PLAYING) {
            mMediaPlayer->setVolume(mVolSlider->value());
        } else if (state == DuLibVlcWrapper::END_OF_MEDIA) {
            if (!ui->actionRepetir->isChecked()) {
                on_actionSiguiente_triggered();
            } else {
                on_actionDetener_triggered();
                on_actionReproducir_triggered();
            }
        }
    });

    connect(mMediaPlayer, &DuLibVlcWrapper::positionChanged,
            [&](float pos) {
        // sets the display and advance the slider
        qint64 total = mMediaPlayer->duration();
        mMediaProgress->setValue(pos*total);
        double msec = total, seg = msec / 1000.0, min = seg / 60.0;
        seg = qint64((min - qint64(min)) * 60.0);
        min = qint64(min);
        auto strTotal = QString::number(min) + ":" + QString::number(seg);
        msec = pos*total;
        seg = msec / 1000.0;
        min = seg / 60.0;
        seg = qint64((min - qint64(min)) * 60.0);
        min = qint64(min);
        auto strCurrent = QString::number(min) + ":" + QString::number(seg);
        mTimerLabel->setText(strCurrent + "/" + strTotal);
    });

    connect(mMediaPlayer, &DuLibVlcWrapper::durationChanged,
            [&](qint64 dur) {
        // sets the max to slider
        mMediaProgress->setMaximum(dur);
    });

    // slider is being modified
    connect(mMediaProgress, &DuMediaPlayerProgressSlider::stop, mMediaPlayer,
            &DuLibVlcWrapper::stop);

    // slider's modification is done
    connect(mMediaProgress, &DuMediaPlayerProgressSlider::play, [&](int pos) {
        if (!mMediaPlayer->hasMedia())
            return;
        on_actionReproducir_triggered();
        mMediaPlayer->setPosition(float(pos)/float(mMediaPlayer->duration()));
    });

    connect(mVolSlider, &DuMediaPlayerVolumeSlider::valueChanged, mMediaPlayer,
            &DuLibVlcWrapper::setVolume);
    connect(mVolSlider, &DuMediaPlayerVolumeSlider::muted, mMediaPlayer,
            &DuLibVlcWrapper::setMute);
}

void DuMediaPlayerMainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}

void DuMediaPlayerMainWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void DuMediaPlayerMainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    e->accept();
}

void DuMediaPlayerMainWindow::dropEvent(QDropEvent *e)
{
    auto urls = e->mimeData()->urls();
    for (const auto &i : urls) {
        ui->listWidget->addItem(new QListWidgetItem(QIcon(":mediafile"),
                i.path().mid(1)));
    }
    e->accept();
}

void DuMediaPlayerMainWindow::closeEvent(QCloseEvent *e)
{
    DuMediaPlayerSettings::save
            (DuMediaPlayerSettings::G_VOL,
             DuMediaPlayerSettings::K_VOL,
             mVolSlider->value());
    DuMediaPlayerSettings::save
            (DuMediaPlayerSettings::G_VOL,
             DuMediaPlayerSettings::K_MUTED,
             mVolSlider->isMuted());
    DuMediaPlayerSettings::save
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_VISIBLE,
             ui->actionPlayList->isChecked());
    DuMediaPlayerSettings::save
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_FLOATING,
             ui->dockWidget->isFloating());
    DuMediaPlayerSettings::save
            (DuMediaPlayerSettings::G_MAINWINDOW,
             DuMediaPlayerSettings::K_MW_GEOMETRY,
             geometry());
    if (ui->dockWidget->isFloating()) {
        DuMediaPlayerSettings::save
                (DuMediaPlayerSettings::G_PLAYLIST,
                 DuMediaPlayerSettings::K_GEOMETRY,
                 ui->dockWidget->geometry());
    }
    e->accept();
}

void DuMediaPlayerMainWindow::on_actionAbrir_triggered()
{
    auto lastDir = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_LAST_LOCATION,
             QDir::currentPath()).toString();
    auto filenames = QFileDialog::getOpenFileNames(this, tr("Abrir"), lastDir);
    if (filenames.isEmpty()) {
        return;
    }
    for (const auto &i : filenames) {
        ui->listWidget->addItem(new QListWidgetItem(QIcon(":mediafile"), i));
    }
    DuMediaPlayerSettings::save
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_LAST_LOCATION,
             QFileInfo(filenames.at(0)).dir().
             absolutePath());
}

void DuMediaPlayerMainWindow::on_actionQuitar_triggered()
{
    close();
}

void DuMediaPlayerMainWindow::on_actionReproducir_triggered()
{
    mMediaPlayer->play();
}

void DuMediaPlayerMainWindow::on_actionPausar_triggered()
{
    mMediaPlayer->pause();
}

void DuMediaPlayerMainWindow::on_actionDetener_triggered()
{
    mMediaPlayer->stop();
}

void DuMediaPlayerMainWindow::on_actionSiguiente_triggered()
{
    int curr = ui->listWidget->currentRow();
    if (curr == ui->listWidget->count()-1) {
        curr = 0;
    } else {
        ++curr;
    }
    ui->listWidget->setCurrentRow(curr);
    setMediaFile(ui->listWidget->item(curr)->text());
    on_actionReproducir_triggered();
}

void DuMediaPlayerMainWindow::on_actionAnterior_triggered()
{
    int curr = ui->listWidget->currentRow();
    if (curr == 0) {
        curr = ui->listWidget->count()-1;
    } else {
        --curr;
    }
    ui->listWidget->setCurrentRow(curr);
    setMediaFile(ui->listWidget->item(curr)->text());
    on_actionReproducir_triggered();
}

void DuMediaPlayerMainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    setMediaFile(index.data().toString());
    on_actionReproducir_triggered();
}

void DuMediaPlayerMainWindow::on_actionPlayList_triggered(bool checked)
{
    ui->dockWidget->setVisible(checked);
}

void DuMediaPlayerMainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actionPlayList->setChecked(visible);
}

void DuMediaPlayerMainWindow::on_actionPantalla_completa_triggered()
{
    if (!mVideoWidget->isFullScreen()) {
        mVideoWidget->setFullScreen(true);
    } else {
        mVideoWidget->setFullScreen(false);
    }
}

void DuMediaPlayerMainWindow::on_actionPreferencias_triggered()
{
    DuMediaPlayerPreferencesDialog D(this);
    D.exec();
}

void DuMediaPlayerMainWindow::on_actionAcerca_de_DuMediaPlayer_triggered()
{
    QMessageBox::about(this, "DuMediaPlayer",
                       tr("Autor: %1\n" \
                          "%2\n" \
                          "Organización: %3\n" \
                          "Fecha: 12 de enero de 2015").
                       arg("Carlos Enrique Duarte Ortiz").
                       arg("Software: DuMediaPlayer").
                       arg("DuarteCorporation"));
}

void DuMediaPlayerMainWindow::on_actionAcerca_de_DuarteCorporation_triggered()
{
    QMessageBox::information(this, "DuarteCorporation",
                             tr("%1 es una empresa de software fundada por\n" \
                                "Carlos Enrique Duarte Ortiz en enero de 2006").
                             arg("DuarteCorporation"));
}

void DuMediaPlayerMainWindow::on_actionManual_de_DuMediaPlayer_triggered()
{
    DuMediaPlayerManualDialog D(this);
    D.exec();
}

void DuMediaPlayerMainWindow::on_actionGuardarListaReproduccion_triggered()
{
    auto lastDir = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_LAST_LOCATION,
             QDir::currentPath()).toString();
    auto filename = QFileDialog::getSaveFileName
            (this, tr("Guardar lista de reproducción"), lastDir,
             tr("Lista de reproducción de DuMediaPlayer (*.dpl);;" \
             "Cualquier archivo (*.*)"));
    if (filename.isEmpty()) {
        return;
    }
    QFile F(filename);
    if (!F.open(QIODevice::Text | QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"),
        tr("No se puede guardar en la ubicación seleccionada. ¿Disco lleno?"));
        return;
    }
    QTextStream T(&F);
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        T << ui->listWidget->item(i)->text() << "\n";
    }
    F.flush();
    F.close();
}

void DuMediaPlayerMainWindow::on_actionAbrirListaReproduccion_triggered()
{
    auto lastDir = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_PLAYLIST,
             DuMediaPlayerSettings::K_LAST_LOCATION,
             QDir::currentPath()).toString();
    auto filename = QFileDialog::getOpenFileName
            (this, tr("Abrir lista de reproducción"), lastDir,
             tr("Lista de reproducción de DuMediaPlayer (*.dpl);;" \
             "Cualquier archivo (*.*)"));
    if (filename.isEmpty()) {
        return;
    }
    QFile F(filename);
    if (!F.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"),
            tr("No se puede abrir el archivo"));
        return;
    }
    QTextStream T(&F);
    while (!T.atEnd()) {
        auto _filename = T.readLine();
        if (_filename != "\n") {
            ui->listWidget->addItem(new QListWidgetItem
                (QIcon(":mediafile"), _filename));
        }
    }
    F.close();
}

void DuMediaPlayerMainWindow::setMediaFile(const QString &filename)
{
    mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
}

void DuMediaPlayerMainWindow::setMediaUri(const QString &uri)
{
    mMediaPlayer->setMedia(QUrl(uri));
}
} // end namespace DuarteCorporation
