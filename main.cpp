#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#define __TEST__ 0

#if __TEST__
#include "testclass.h"

    QTEST_MAIN(TestClass);
#else
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "onvifdemo_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}

#endif





