#include "mainwindow.h"
#include <QSettings>
#include "inputdialog.h"
#include "aestools.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QScreen>
#include <QKeyEvent>
#include <QDBusInterface>
#include "qwidgetresizehandler_p.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(qApp->primaryScreen()->size());

    setWindowFlags(Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint);
    setWindowOpacity(0.8);

    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    setPalette(palette);
    //QSettings settings;  //测试使用代码
    //settings.clear();
    showFullScreen();

    QDBusInterface temp("com.deepin.daemon.Zone",
                        "/com/deepin/daemon/Zone",
                        "com.deepin.daemon.Zone",
                        QDBusConnection::sessionBus(),
                        NULL);
    temp.call("EnableZoneDetected", false);//禁用热区
}

MainWindow::~MainWindow()
{
    QDBusInterface temp("com.deepin.daemon.Zone",
                        "/com/deepin/daemon/Zone",
                        "com.deepin.daemon.Zone",
                        QDBusConnection::sessionBus(),
                        NULL);
    temp.call("EnableZoneDetected", true);//启用热区
}

void MainWindow::init()
{
    QSettings settings;
    //qDebug()<<settings.fileName();
    QByteArray key = settings.value("Key", "").toByteArray();

    if(!keyIsPermissible(key)){
        dialog = new InputDialog(this);
        dialog->show();

        key = dialog->getText().toLatin1().toUpper();

        while(!keyIsPermissible(key)&&dialog->isVisible()){
            QMessageBox messagebox(this);
            QWidgetResizeHandler *temp = new QWidgetResizeHandler(&messagebox);
            temp->setMovingEnabled(true);
            messagebox.setWindowFlags(Qt::ToolTip|Qt::WindowStaysOnTopHint);
            messagebox.setFixedSize(180,50);
            messagebox.setDefaultButton(QMessageBox::Ok);
            messagebox.setText(tr("Secret key validation fails"));
            messagebox.move(qApp->desktop()->width()/2-messagebox.width()/2,
                            dialog->y()-messagebox.height()*2);
            messagebox.exec();
            temp->deleteLater();

            key = dialog->getText().toLatin1();
        }

        if(dialog->isVisible()){
            dialog->close();
            settings.setValue("Key", key);
        }
    }
    close();
    qApp->quit();
}

bool MainWindow::keyIsPermissible(const QByteArray &key) const
{
    if(key.length() == 20){
        AESTools tools("qwertyuiop[]';lk");
        QByteArray temp = tools.Encrypt(key.left(10)).toHex().toUpper();
        QByteArray result;
        QByteArray array="123456789QWERTYUIOPASDFGHJKLZXCV";

        for(int i=0;i<10; ++i){
            result.append(temp[array.indexOf(key[i])]);
        }

        if(key.right(10) == result){
            return true;
        }
    }

    return false;
}
