#include "DuMediaPlayerSettings.h"
#include <QSettings>

namespace DuarteCorporation
{
const QString DuMediaPlayerSettings::G_PLAYLIST = "G_PLAYLIST";
const QString DuMediaPlayerSettings::G_VOL = "G_VOL";
const QString DuMediaPlayerSettings::G_SETTINGS = "G_SETTINGS";
const QString DuMediaPlayerSettings::G_MAINWINDOW = "G_MAINWINDOW";
const QString DuMediaPlayerSettings::K_LAST_LOCATION = "K_LAST_LOCATION";
const QString DuMediaPlayerSettings::K_VOL = "K_VOL";
const QString DuMediaPlayerSettings::K_MUTED = "K_MUTED";
const QString DuMediaPlayerSettings::K_VISIBLE = "K_VISIBLE";
const QString DuMediaPlayerSettings::K_FLOATING = "K_FLOATING";
const QString DuMediaPlayerSettings::K_GEOMETRY = "K_GEOMETRY";
const QString DuMediaPlayerSettings::K_LANGUAJE = "K_LANGUAJE";
const QString DuMediaPlayerSettings::K_STYLE = "K_STYLE";
const QString DuMediaPlayerSettings::K_MW_GEOMETRY = "K_MW_GEOMETRY";

void DuMediaPlayerSettings::save(const QString &g, const QString &k,
                                 const QVariant &v)
{
    QSettings S;
    S.beginGroup(g);
    S.setValue(k, v);
    S.endGroup();
}

QVariant DuMediaPlayerSettings::load(const QString &g, const QString &k,
                                     const QVariant &dv)
{
    QSettings S;
    S.beginGroup(g);
    auto v = S.value(k, dv);
    S.endGroup();
    return v;
}
} // end namespace DuarteCorporation
