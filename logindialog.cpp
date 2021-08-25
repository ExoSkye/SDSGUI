#include "logindialog.h"
#include "ui_logindialog.h"
#include <QUrl>
#include <QDesktopServices>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    QDesktopServices::setUrlHandler("sds",this,"getSession");
    QDesktopServices::openUrl(QUrl("sds://aaa"));
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::getSession(const QUrl &url) {
    ui->label->setText(url.path());
}
