#include <QApplication>
#include "mainwindow.h"
#include "aestools.h"
#include <QTime>
#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>

/*QByteArray test()
{
    QByteArray result;
    QByteArray array="123456789QWERTYUIOPASDFGHJKLZXCV";


    for(int i=0;i<10;++i){
        result.append(array[qrand()%array.length()]);
    }

    return result;
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("activationVerification");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("deepin");

    QString locale = QLocale::system().name();
    QTranslator qtTranslator;
    if (qtTranslator.load("qt_"+locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&qtTranslator);
    QTranslator translator;
    if (translator.load(a.applicationName()+"_"+locale, ":/i18n/"))
        a.installTranslator(&translator);

    MainWindow window;
    window.init();

    /*AESTools tools("qwertyuiop[]';lk");

    QTime t = QTime::currentTime();
    qsrand(t.msec()*100000);

    for(int i=0;i<100;++i){
        QByteArray temp = test();
        QByteArray result;
        QByteArray temp2 = tools.Encrypt(temp).toHex();
        QByteArray array="123456789QWERTYUIOPASDFGHJKLZXCV";

        for(int i=0;i<10; ++i){
            result.append(temp2[array.indexOf(temp[i])]);
        }

        if(result.contains('0')){
            --i;
            continue;
        }

        qDebug()<<temp+result.toUpper();

    }*/

    return 0;
}
