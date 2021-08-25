#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSettings>

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SDSGUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
#ifdef _WIN32
    char pBuf[512];
    int bytes = GetModuleFileNameA(NULL, pBuf, 512);

    strcpy(pBuf[bytes-6],"TOKEN_PLACER")

    QSettings key("HKEY_CLASSES_ROOT\\sds", QSettings::NativeFormat);
    key.setValue(".","URL:sds Protocol");
    key.setValue("URL Protocol", "");
    QSettings OpenKey("HKEY_CLASSES_ROOT\\sds\\shell\\open\\command", QSettings::NativeFormat);
    OpenKey.setValue(".", std::string(pBuf));
#endif

    MainWindow w;
    w.show();
    return a.exec();
}
