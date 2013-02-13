#include "getnameapp.h"
#include "ui_getnameapp.h"


#include <QDebug>
kXneurApp::getNameApp::getNameApp(QWidget *parent) :    QDialog(parent),    ui(new Ui::getNameApp)
{
    ui->setupUi(this);
    //setAttribute( Qt::WA_DeleteOnClose, true);
    Xprop = new QProcess();
    connect(ui->cmdBox, SIGNAL(clicked(QAbstractButton*)), SLOT(Clicked(QAbstractButton*)));
    connect(ui->cmdGetApp, SIGNAL(clicked()), SLOT(getApp()));
    connect(Xprop, SIGNAL(readyRead()), SLOT(readOutput()));
}

kXneurApp::getNameApp::~getNameApp()
{
    delete ui;
}

void kXneurApp::getNameApp::Clicked(QAbstractButton *cmd)
{
    if(ui->cmdBox->standardButton(cmd) == QDialogButtonBox::Ok)
    {
        if(ui->txtNameApp->text().trimmed().isEmpty())
        {
            QMessageBox::information(0, tr("Applecation name is empty"), tr("You don't specify the application name."), QMessageBox::Ok);
        }
        else
        {
            done(QDialog::Accepted);
            appName = ui->txtNameApp->text();
            this->close();
        }
    }
    else
    {
        done(QDialog::Rejected);
        this->close();
    }
}

void kXneurApp::getNameApp::getApp()
{
    Xprop->start("xprop WM_CLASS");
}

void kXneurApp::getNameApp::readOutput()
{
    QString str = Xprop->readAllStandardOutput();
    ui->txtNameApp->setText(str.remove(0,19).split(",").at(1).trimmed().replace("\"",""));
}
