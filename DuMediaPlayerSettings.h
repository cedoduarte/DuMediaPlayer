#ifndef DUMEDIAPLAYERSETTINGS_H
#define DUMEDIAPLAYERSETTINGS_H

#include <QVariant>

namespace DuarteCorporation
{
class DuMediaPlayerSettings
{
public:
    static void save(const QString &g, const QString &k, const QVariant &v);
    static QVariant load(const QString &g, const QString &k,
                         const QVariant &dv = QVariant());

    static const QString G_PLAYLIST;
    static const QString G_VOL;
    static const QString G_SETTINGS;
    static const QString G_MAINWINDOW;
    static const QString K_LAST_LOCATION;
    static const QString K_VISIBLE;
    static const QString K_VOL;
    static const QString K_MUTED;
    static const QString K_FLOATING;
    static const QString K_GEOMETRY;
    static const QString K_LANGUAJE;
    static const QString K_STYLE;
    static const QString K_MW_GEOMETRY;
};
} // end namespace DuarteCorporation

#endif // DUMEDIAPLAYERSETTINGS_H
