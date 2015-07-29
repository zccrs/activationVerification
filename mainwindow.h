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

private:
    InputDialog *dialog;

    bool keyIsPermissible(const QByteArray& key) const;
};

#endif // MAINWINDOW_H
