#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class InputDialog;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();
    bool keyIsPermissible(const QByteArray& key) const;
private:
    InputDialog *dialog;
};

#endif // MAINWINDOW_H
