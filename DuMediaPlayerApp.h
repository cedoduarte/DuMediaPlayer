#ifndef DUMEDIAPLAYERAPP_H
#define DUMEDIAPLAYERAPP_H

class QTranslator;
class QApplication;

namespace DuarteCorporation
{
class DuMediaPlayerMainWindow;

class DuMediaPlayerApp
{
public:
    DuMediaPlayerApp(int argc, char **argv);
    ~DuMediaPlayerApp();
    int exec();
private:
    void setSettings();
    void setLanguage();
    void setStyle();

    QApplication *mApp;
    QTranslator *mTrans;
    DuMediaPlayerMainWindow *mMediaPlayer;
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERAPP_H
