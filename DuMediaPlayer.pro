#-------------------------------------------------
#
# Project created by QtCreator 2015-01-11T17:34:55
#
#-------------------------------------------------

QT += core \
      gui \
      multimedia \
      multimediawidgets \
      widgets \
      webkitwidgets \
      webkit

TARGET = DuMediaPlayer

TEMPLATE = app

SOURCES += \
    DuMediaPlayerMainWindow.cpp \
    DuMediaPlayerProgressSlider.cpp \
    DuMediaPlayerListWidget.cpp \
    DuMediaPlayerSettings.cpp \
    DuMediaPlayerVolumeSlider.cpp \
    DuMediaPlayerVideoWidget.cpp \
    DuMediaPlayerPreferencesDialog.cpp \
    DuMediaPlayerManualDialog.cpp \
    main.cpp \
    DuMediaPlayerApp.cpp \
    DuLibVlcWrapper.cpp

HEADERS  += \
    DuMediaPlayerMainWindow.h \
    DuMediaPlayerProgressSlider.h \
    DuMediaPlayerListWidget.h \
    DuMediaPlayerSettings.h \
    DuMediaPlayerVolumeSlider.h \
    DuMediaPlayerVideoWidget.h \
    DuMediaPlayerPreferencesDialog.h \
    DuMediaPlayerManualDialog.h \
    DuMediaPlayerApp.h \
    DuLibVlcWrapper.h

FORMS    += \
    DuMediaPlayerMainWindow.ui \
    DuMediaPlayerVolumeSlider.ui \
    DuMediaPlayerPreferencesDialog.ui \
    DuMediaPlayerManualDialog.ui

QMAKE_CXXFLAGS += -std=gnu++14

RESOURCES += res.qrc

RC_ICONS = mainicon.ico

INCLUDEPATH += $$PWD/3rdParty/vlc-2.1.5/sdk/include

LIBS += -L$$PWD/3rdParty/vlc-2.1.5/sdk/lib -llibvlccore -llibvlc
