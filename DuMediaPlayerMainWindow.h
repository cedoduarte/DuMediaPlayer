#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QLabel;

namespace DuarteCorporation
{
class DuLibVlcWrapper;
class DuMediaPlayerVideoWidget;
class DuMediaPlayerVolumeSlider;
class DuMediaPlayerProgressSlider;

class DuMediaPlayerMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DuMediaPlayerMainWindow(int argc, char **argv,
                                     QWidget *parent = nullptr);
    ~DuMediaPlayerMainWindow();

    DuLibVlcWrapper *mediaPlayer() const
    {
        return mMediaPlayer;
    }
protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);
    void closeEvent(QCloseEvent *e);
private slots:
    void on_actionAbrir_triggered();
    void on_actionQuitar_triggered();
    void on_actionPausar_triggered();
    void on_actionDetener_triggered();
    void on_actionAnterior_triggered();
    void on_actionSiguiente_triggered();
    void on_actionReproducir_triggered();
    void on_actionPreferencias_triggered();
    void on_actionPantalla_completa_triggered();
    void on_actionPlayList_triggered(bool checked);
    void on_actionAbrirListaReproduccion_triggered();
    void on_actionAcerca_de_DuMediaPlayer_triggered();
    void on_actionManual_de_DuMediaPlayer_triggered();
    void on_actionGuardarListaReproduccion_triggered();
    void on_dockWidget_visibilityChanged(bool visible);
    void on_listWidget_clicked(const QModelIndex &index);
    void on_actionAcerca_de_DuarteCorporation_triggered();
private:
    void initialize();
    void applySettings(int argc, char **argv);
    void connections();
    void setMediaFile(const QString &filename);
    void setMediaUri(const QString &uri);

    DuMediaPlayerProgressSlider *mMediaProgress;
    DuMediaPlayerVideoWidget *mVideoWidget;
    DuMediaPlayerVolumeSlider *mVolSlider;
    DuLibVlcWrapper *mMediaPlayer;
    QLabel *mTimerLabel;
    Ui::MainWindow *ui;
};
} // end namespace DuarteCorporation

#endif // MAINWINDOW_H
