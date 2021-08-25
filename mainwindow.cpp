#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("School Digital Signage Management Interface");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_pressed()
{
    loginDialog login(this);
    login.exec();
}

