#pragma once

#include <QDialog>
#include "ui_manageaccount.h"

class ManageAccount : public QDialog
{
    Q_OBJECT

public:
    ManageAccount(const QString& username, const QString& password, QWidget* parent = Q_NULLPTR);
    QString username;
    QString password;
    ~ManageAccount();

private slots:

    void on_backBtn_clicked();
    void on_deleteBtn_clicked();
    void on_changeBtn_clicked();

private:
    Ui::ManageAccount ui;
};