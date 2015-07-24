#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QLabel>
#include <QEventLoop>
#include <QLineEdit>

class QLineEdit;
class InputDialog : public QWidget
{
    Q_OBJECT

public:
    InputDialog(QWidget *parent = 0);
    ~InputDialog();

    QString getText();
    void quitLoop();
private:
    QLineEdit edit;
    QLabel title;

    QEventLoop *loop;

    void init();
};
#endif // INPUTDIALOG_H
