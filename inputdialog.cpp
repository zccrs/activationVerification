#include "inputdialog.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QMouseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include "qwidgetresizehandler_p.h"
//测试此类是否能正常使用

InputDialog::InputDialog(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_QuitOnClose);
    setWindowFlags(Qt::ToolTip|Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setFixedSize(240, 180);
    move(qApp->desktop()->width()/2-width()/2, qApp->desktop()->height()/2-height()/2);

    init();

    QWidgetResizeHandler *temp = new QWidgetResizeHandler(this);
    temp->setMovingEnabled(true);
}

InputDialog::~InputDialog()
{
}

QString InputDialog::getText()
{
    if(!loop->isRunning()&&isVisible())
        loop->exec();

    return edit.text().replace('-', "");
}

void InputDialog::quitLoop()
{
    loop->quit();
}

void InputDialog::init()
{
    loop = new QEventLoop(this);

    edit.setInputMask("NNNNN-NNNNN-NNNNN-NNNNN;0");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    title.setText(tr("Please enter a secret key"));
    title.setMaximumHeight(15);

    mainLayout->addWidget(&title);

    QHBoxLayout *hlayout1 = new QHBoxLayout(NULL);
    hlayout1->addItem(new QSpacerItem(10, 10));
    hlayout1->addWidget(&edit);
    hlayout1->addItem(new QSpacerItem(10, 10));

    QHBoxLayout *hlayout2 = new QHBoxLayout(NULL);
    hlayout2->addItem(new QSpacerItem(width()*0.8,20));

    QPushButton *button_quit = new QPushButton(NULL);
    button_quit->setText(tr("Quit"));
    connect(button_quit, &QPushButton::clicked, [&](){
        loop->quit();
        close();
    });
    hlayout2->addWidget(button_quit);
    QPushButton *button = new QPushButton(NULL);
    button->setText(tr("OK"));
    button->setFocus();
    button->setDefault(true);
    button->setShortcut(QKeySequence::InsertParagraphSeparator);
    connect(button, &QAbstractButton::clicked, loop, &QEventLoop::quit);
    hlayout2->addWidget(button);

    mainLayout->addLayout(hlayout1);
    mainLayout->addLayout(hlayout2);

    edit.grabKeyboard();
}
