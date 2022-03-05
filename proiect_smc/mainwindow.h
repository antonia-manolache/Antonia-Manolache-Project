#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "account.h"
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include<QMessageBox>
#include <QDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void on_SignUpBtn_clicked();

    void on_LogInBtn_clicked();

private:
    Ui::MainWindowClass ui;
    QSqlDatabase database;
};

