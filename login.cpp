#include "login.h"
#include "ui_login.h"

#include <QAbstractSocket>
#include <QNetworkInterface>
#include <QList>
#include <QDebug>

Login::Login(GameViewer *game_viewer) :
    QDialog(),
    ui(new Ui::Login)
{
    gviewer = game_viewer;
    ui->setupUi(this);
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QString ips;
    for(int nIter=0; nIter<list.count(); nIter++)
    {
        if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                if(ips.isEmpty())
                    ips = list[nIter].toString();
                else
                    ips += " | " +list[nIter].toString();
    }
    ui->txtIpServer->setText(ips);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OnOkClick()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(OnCancelClick()));
}

Login::~Login()
{
    delete ui;
}

void Login::OnOkClick()
{
    gviewer->setIP(ui->rdServer->isChecked(), ui->txtIpServer->text());
}

void Login::OnCancelClick()
{
    qDebug() << "CANCEL CLICK";
}
