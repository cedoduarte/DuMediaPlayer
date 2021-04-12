#include "DuMediaPlayerPreferencesDialog.h"
#include "DuMediaPlayerMainWindow.h"
#include "DuMediaPlayerSettings.h"
#include "DuMediaPlayerApp.h"
#include <QApplication>
#include <QTranslator>

namespace DuarteCorporation
{
DuMediaPlayerApp::DuMediaPlayerApp(int argc, char **argv)
{
    mApp = new QApplication(argc, argv);
    setSettings();
    mTrans = new QTranslator;
    setLanguage();
    setStyle();    
    mMediaPlayer = new DuMediaPlayerMainWindow(argc, argv);
}

DuMediaPlayerApp::~DuMediaPlayerApp()
{
    delete mMediaPlayer;
    delete mTrans;
    delete mApp;
}

int DuMediaPlayerApp::exec()
{
    mMediaPlayer->show();
    return mApp->exec();
}

void DuMediaPlayerApp::setSettings()
{
  mApp->setApplicationName("DuMediaPlayer");
  mApp->setApplicationVersion("1.0");
  mApp->setOrganizationName("DuarteCorporation");
  mApp->setOrganizationDomain("https://www.youtube.com/user/duartecorporation");
}

void DuMediaPlayerApp::setLanguage()
{
    int lang = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_SETTINGS,
             DuMediaPlayerSettings::K_LANGUAJE,
             DuMediaPlayerPreferencesDialog::ENGLISH).toInt();
    switch (lang) {
    case DuMediaPlayerPreferencesDialog::ENGLISH:
        mTrans->load(":lang/en.qm");
        break;
    case DuMediaPlayerPreferencesDialog::PORTUGUESE:
        mTrans->load(":lang/pt.qm");
        break;
    case DuMediaPlayerPreferencesDialog::RUSSIAN:
        mTrans->load(":lang/ru.qm");
        break;
    case DuMediaPlayerPreferencesDialog::CHINESE:
        mTrans->load(":lang/ch.qm");
        break;
    case DuMediaPlayerPreferencesDialog::FRENCH:
        mTrans->load(":lang/fr.qm");
        break;
    case DuMediaPlayerPreferencesDialog::ITALIAN:
        mTrans->load(":lang/it.qm");
        break;
    case DuMediaPlayerPreferencesDialog::GERMAN:
        mTrans->load(":lang/ge.qm");
        break;
    case DuMediaPlayerPreferencesDialog::JAPANESE:
        mTrans->load(":lang/jp.qm");
        break;
    }
    if (lang != DuMediaPlayerPreferencesDialog::SPANISH) {
        mApp->installTranslator(mTrans);
    }
}

void DuMediaPlayerApp::setStyle()
{
    int style = DuMediaPlayerSettings::load
            (DuMediaPlayerSettings::G_SETTINGS,
             DuMediaPlayerSettings::K_STYLE,
             DuMediaPlayerPreferencesDialog::FUSION).toInt();
    switch (style) {
    case DuMediaPlayerPreferencesDialog::WINDOWS_VISTA:
        mApp->setStyle("windowsvista");
        break;
    case DuMediaPlayerPreferencesDialog::FUSION:
        mApp->setStyle("fusion");
        break;
    }
}
} // end namespace DuarteCorporation
